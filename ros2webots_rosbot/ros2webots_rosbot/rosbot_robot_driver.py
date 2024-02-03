#!/usr/bin/env python3

import rclpy
from rclpy.qos import QoSProfile
import time

from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState


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

        # self.__fl_wheel_twist = Twist()
        # self.__fr_wheel_twist = Twist()
        # self.__rl_wheel_twist = Twist()
        # self.__rr_wheel_twist = Twist()

        self.__wheels_encoder_data = JointState()

        rclpy.init(args=None)

        self.__node = rclpy.create_node('webots_rosbot_driver_node')
        self.__node.create_subscription(Twist, '/webots/rosbot/command_vel', self.__cmd_vel_callback, 10)


        self.__publisher_wheels_encoder_data = self.__node.create_publisher(JointState, '/webots/rosbot/odom/wheels_encoder_data', QoSProfile(depth=10))
        self.__node.create_timer(0.05, self.__publish_wheels_encoder_data)
        

    def __publish_wheels_encoder_data(self):
        current_time = time.time()
        self.__wheels_encoder_data.header.stamp.sec = int(current_time)
        self.__wheels_encoder_data.header.stamp.nanosec = int((current_time - int(current_time)) * 1e9)
        self.__wheels_encoder_data.position = [self.__fl_sensor.getValue(), self.__fr_sensor.getValue(), self.__rl_sensor.getValue(), self.__rr_sensor.getValue()]
        self.__publisher_wheels_encoder_data.publish(self.__wheels_encoder_data)

    
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