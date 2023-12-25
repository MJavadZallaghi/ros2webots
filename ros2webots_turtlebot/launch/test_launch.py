from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='webots_ros2_dev_1',
            namespace='sim_node_run_1',
            executable='sim_node_ros2webots',
            name='sim'
        ),
    ])