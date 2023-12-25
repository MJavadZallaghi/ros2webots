from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions.path_join_substitution import PathJoinSubstitution
from webots_ros2_driver.webots_launcher import WebotsLauncher

def generate_launch_description():

    # start webots 
    # webots = WebotsLauncher (

    # )
    return LaunchDescription([
        Node(
            package='webots_ros2_dev_1',
            namespace='sim_node_run_1',
            executable='sim_node_ros2webots',
            name='sim'
        ),
    ])