from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions.path_join_substitution import PathJoinSubstitution
from webots_ros2_driver.webots_launcher import WebotsLauncher
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
import launch
from webots_ros2_driver.webots_controller import WebotsController
import datetime

def generate_launch_description():

    package_dir = get_package_share_directory('ros2webots_manipulator')
    world = LaunchConfiguration('world')

    # start webots 
    webots = WebotsLauncher (
        world=PathJoinSubstitution([package_dir, 'worlds', world]),
        ros2_supervisor=True
    )

    # start robot <extern> controller
    robot_description_path = PathJoinSubstitution([package_dir, 'resource', 'nedComponent.urdf'])
    rosBot_driver = WebotsController(
        robot_name='ned_robot',
        parameters=[{'robot_description':robot_description_path}
        ],
        respawn=True
    )


    

    # ned data logging
    # Construct the bag file name with the timestamp
    current_time = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    bag_file_name = '/home/mjavadzallaghi/ros2_ws/ros2webots/baglog/' + f'rosbot_data_{current_time}'
    rosbot_logger_node = launch.actions.ExecuteProcess(

            cmd=['ros2', 'bag', 'record', '/tf', '/webots/ned/sensors/joinsState', '/webots/ned/command_pos', '-o', bag_file_name],   
            output='screen',
        )
    
    foxglove_beidge = launch.actions.ExecuteProcess(
            cmd=['ros2', 'launch', 'foxglove_bridge', 'foxglove_bridge_launch.xml'],   
            output='screen',
        ) 

    return LaunchDescription([
        DeclareLaunchArgument(
            'world',
            default_value='world_roboticknowledge.wbt',
            description='Choose one of the world files from `/ros2webots_manipulator/worlds/world` directory'
        ),
        webots,
        webots._supervisor,
        rosBot_driver,
        rosbot_logger_node,
        foxglove_beidge,


        # This action will kill all nodes once the Webots simulation has exited
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=webots,
                on_exit=[
                    launch.actions.EmitEvent(event=launch.events.Shutdown())
                ],
            )
        )
    ])