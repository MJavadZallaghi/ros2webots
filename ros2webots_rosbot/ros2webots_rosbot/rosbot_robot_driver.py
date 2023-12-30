#!/usr/bin/env python3

import rclpy

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

        self.__target_twist = Twist()

        rclpy.init(args=None)

        self.__node = rclpy.create_node('webots_rosbot_driver_node')
        self.__node.create_subscription(Twist, '/webots/rosbot/command_vel', self.__cmd_vel_callback, 10)

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