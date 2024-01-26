#!/usr/bin/env python3

import rclpy
from rclpy.qos import QoSProfile
import time

from geometry_msgs.msg import Twist

HALF_DISTANCE_BETWEEN_WHEELS = 0.045
WHEEL_RADIUS = 0.025

class RosBotWebotsDriver():
    def init(self, webots_node, properties):
        self.__robot = webots_node.robot

        self.__fl_motor = self.__robot.getDevice('fl_wheel_joint')
        self.__fr_motor = self.__robot.getDevice('fr_wheel_joint')
        self.__rl_motor = self.__robot.getDevice('rl_wheel_joint')
        self.__rr_motor = self.__robot.getDevice('rr_wheel_joint')

        self.__fl_motor.setPosition(float('inf'))
        self.__fl_motor.setVelocity(0)

        self.__fr_motor.setPosition(float('inf'))
        self.__fr_motor.setVelocity(0)

        self.__rl_motor.setPosition(float('inf'))
        self.__rl_motor.setVelocity(0)

        self.__rr_motor.setPosition(float('inf'))
        self.__rr_motor.setVelocity(0)

        self.__fl_sensor = self.__robot.getDevice('front left wheel motor sensor')
        self.__fr_sensor = self.__robot.getDevice('front right wheel motor sensor')
        self.__rl_sensor = self.__robot.getDevice('rear left wheel motor sensor')
        self.__rr_sensor = self.__robot.getDevice('rear right wheel motor sensor')

        self.__fl_sensor.enable(50) #50 in ms based on the doc
        self.__fr_sensor.enable(50) #50 in ms based on the doc
        self.__rl_sensor.enable(50) #50 in ms based on the doc
        self.__rr_sensor.enable(50) #50 in ms based on the doc

        self.__target_twist = Twist()

        self.__fl_wheel_twist = Twist()
        self.__fr_wheel_twist = Twist()
        self.__rl_wheel_twist = Twist()
        self.__rr_wheel_twist = Twist()

        rclpy.init(args=None)

        self.__node = rclpy.create_node('webots_rosbot_driver_node')
        self.__node.create_subscription(Twist, '/webots/rosbot/command_vel', self.__cmd_vel_callback, 10)

        self.__publisher_fl_wheel_data = self.__node.create_publisher(Twist, '/webots/rosbot/odom/fl_wheel_pose', QoSProfile(depth=10))
        self.__timer_fl_wheel_pose = self.__node.create_timer(1.0 / 20, self.__publish_twist_fl_wheel_data)
        self.__publisher_fr_wheel_data = self.__node.create_publisher(Twist, '/webots/rosbot/odom/fr_wheel_pose', QoSProfile(depth=10))
        self.__timer_fr_wheel_pose = self.__node.create_timer(1.0 / 20, self.__publish_twist_fr_wheel_data)
        self.__publisher_rl_wheel_data = self.__node.create_publisher(Twist, '/webots/rosbot/odom/rl_wheel_pose', QoSProfile(depth=10))
        self.__timer_rl_wheel_pose = self.__node.create_timer(1.0 / 20, self.__publish_twist_rl_wheel_data)
        self.__publisher_rr_wheel_data = self.__node.create_publisher(Twist, '/webots/rosbot/odom/rr_wheel_pose', QoSProfile(depth=10))
        self.__timer_rr_wheel_pose = self.__node.create_timer(1.0 / 20, self.__publish_twist_rr_wheel_data)
        

    def __publish_twist_fl_wheel_data(self):
        self.__fl_wheel_twist.angular.z = self.__fl_sensor.getValue()
        self.__publisher_fl_wheel_data.publish(self.__fl_wheel_twist)
    
    def __publish_twist_fr_wheel_data(self):
        self.__fr_wheel_twist.angular.z = self.__fr_sensor.getValue()
        self.__publisher_fr_wheel_data.publish(self.__fr_wheel_twist)
    
    def __publish_twist_rl_wheel_data(self):
        self.__rl_wheel_twist.angular.z = self.__rl_sensor.getValue()
        self.__publisher_rl_wheel_data.publish(self.__rl_wheel_twist)
    
    def __publish_twist_rr_wheel_data(self):
        self.__rr_wheel_twist.angular.z = self.__rr_sensor.getValue()
        self.__publisher_rr_wheel_data.publish(self.__rr_wheel_twist)

    
    def __cmd_vel_callback(self, twist):
        self.__target_twist = twist

    def step(self):
        rclpy.spin_once(self.__node, timeout_sec=0)

        forward_speed = self.__target_twist.linear.x
        angular_speed = self.__target_twist.angular.z

        command_motor_left = (forward_speed - angular_speed * HALF_DISTANCE_BETWEEN_WHEELS) / WHEEL_RADIUS
        command_motor_right = (forward_speed + angular_speed * HALF_DISTANCE_BETWEEN_WHEELS) / WHEEL_RADIUS

        self.__fl_motor.setVelocity(command_motor_left)
        self.__rl_motor.setVelocity(command_motor_left)
        self.__fr_motor.setVelocity(command_motor_right)
        self.__rr_motor.setVelocity(command_motor_right)