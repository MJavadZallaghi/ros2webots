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

    package_dir = get_package_share_directory('ros2webots_rosbot')
    world = LaunchConfiguration('world')

    # start webots 
    webots = WebotsLauncher (
        world=PathJoinSubstitution([package_dir, 'worlds', world]),
        ros2_supervisor=True
    )

    # start robot <extern> controller
    robot_description_path = PathJoinSubstitution([package_dir, 'resource', 'rosBotComponent.urdf'])
    rosBot_driver = WebotsController(
        robot_name='rosbot_robot',
        parameters=[{'robot_description':robot_description_path}
        ],
        respawn=True
    )
    # RUN TF and URDF publisher node of the rosbot for robot visualization
    ros_tf_urdf_pub_node = Node(
        package='ros2webots_rosbot',
        namespace='rosbot_tf_urdf_pub_node',
        executable='rosbot_tf_publisher',
        name='rosbot_tf_urdf_pub_node',
        )
    # Run imu-based localization node for the rosbot
    # rosbot_localization_configue_file = PathJoinSubstitution([package_dir, 'resource', 'rosbot_robot_localization.yaml'])
    # rosbot_localization_node = Node(
    #         package='robot_localization',
    #         executable='ekf_node',
    #         name='ekf_filter_node',
    #         output='screen',
    #         arguments=[rosbot_localization_configue_file],
    #     )

    # Localization Node
    rosbo_localization_model_node = Node(
        package='ros2webots_rosbot',
        namespace='rosbot_localization_node_1',
        executable='rosbot_localization_node',
        name='rosbot_localization_node_1',
        )

    # rosbot data logging
    # Construct the bag file name with the timestamp
    current_time = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    bag_file_name = '/home/mjavadzallaghi/ros2_ws/ros2webots/baglog/' + f'rosbot_data_{current_time}'
    rosbot_logger_node = launch.actions.ExecuteProcess(
            cmd=['ros2', 'bag', 'record', '/webots/rosbot/imu', 'ros2/rosbot/odometry', '/webots/rosbot/odom/wheels_encoder_data', '/webots/rosbot/command_vel', '-o', bag_file_name],   
            output='screen',
        )

    return LaunchDescription([
        DeclareLaunchArgument(
            'world',
            default_value='world_roboticknowledge.wbt',
            description='Choose one of the world files from `/ros2webots_rosbot/worlds/world` directory'
        ),
        webots,
        webots._supervisor,
        rosBot_driver,
        ros_tf_urdf_pub_node,
        # rosbot_localization_node,
        rosbo_localization_model_node,
        rosbot_logger_node,


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