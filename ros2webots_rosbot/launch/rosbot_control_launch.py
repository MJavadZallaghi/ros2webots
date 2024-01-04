from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # start the node for getting velocity command for rosbot from keyboard
    Node(
        package='ros2webots_rosbot',
        namespace='rosbot_keyboard_node_get_velocity',
        executable='rosbot_get_keyboard_command',
        name='rosbot_keyboard_node_get_velocity',
        emulate_tty=True,
        ),
    ])