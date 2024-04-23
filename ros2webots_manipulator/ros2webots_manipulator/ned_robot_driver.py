#!/usr/bin/env python3

# TODO: Currently only position command is be provided for the Ned.
# Later, Torque command interface must be added too (depends on moveit2 common interface)

import rclpy
from rclpy.qos import QoSProfile
import time

from sensor_msgs.msg import JointState


class NedWebotsDriver():
    def init(self, webots_node, properties):
        self.__robot = webots_node.robot

        
        self.__joint_1 = self.__robot.getDevice('joint_1')
        self.__joint_1.setPosition(0) # 2.8
        self.__joint_2 = self.__robot.getDevice('joint_2')
        self.__joint_2.setPosition(0) # 0.8
        self.__joint_3 = self.__robot.getDevice('joint_3')
        self.__joint_3.setPosition(0) # 1.3
        self.__joint_4 = self.__robot.getDevice('joint_4')
        self.__joint_4.setPosition(0) # 2.0
        self.__joint_5 = self.__robot.getDevice('joint_5')
        self.__joint_5.setPosition(0) # 1.5
        self.__joint_6 = self.__robot.getDevice('joint_6')
        self.__joint_6.setPosition(0) # 2.5
        self.__gripper = self.__robot.getDevice('gripper::left')
        self.__gripper.setPosition(0) # 0.0

        



        self.__joint_1_sensor = self.__robot.getDevice('joint_1_sensor')
        self.__joint_2_sensor = self.__robot.getDevice('joint_2_sensor')
        self.__joint_3_sensor = self.__robot.getDevice('joint_3_sensor')
        self.__joint_4_sensor = self.__robot.getDevice('joint_4_sensor')
        self.__joint_5_sensor = self.__robot.getDevice('joint_5_sensor')
        self.__joint_6_sensor = self.__robot.getDevice('joint_6_sensor')
        self.__gripper_sensor = self.__robot.getDevice('gripper::left_sensor')


        self.__joint_1_sensor.enable(50) #50 in ms based on the doc
        self.__joint_2_sensor.enable(50) 
        self.__joint_3_sensor.enable(50) 
        self.__joint_4_sensor.enable(50) 
        self.__joint_5_sensor.enable(50) 
        self.__joint_6_sensor.enable(50) 
        self.__gripper_sensor.enable(50) 


        self.__joints_encoder_data = JointState()

        rclpy.init(args=None)

        self.__node = rclpy.create_node('webots_ned_driver_node')
        self.__target_JointState = JointState()
        self.__node.create_subscription(JointState, '/webots/ned/command_pos', self.__cmd_pos_callback, 10)


        self.__publisher_joints_encoder_data = self.__node.create_publisher(JointState, '/webots/ned/sensors/joinsState', QoSProfile(depth=10))
        self.__node.create_timer(0.05, self.__publish_joints_encoder_data)
        

    def __publish_joints_encoder_data(self):
        current_time = time.time()
        self.__joints_encoder_data.header.stamp.sec = int(current_time)
        self.__joints_encoder_data.header.stamp.nanosec = int((current_time - int(current_time)) * 1e9)
        self.__joints_encoder_data.position = [self.__joint_1_sensor.getValue(),self.__joint_2_sensor.getValue(),self.__joint_3_sensor.getValue(),self.__joint_4_sensor.getValue(),self.__joint_5_sensor.getValue(),self.__joint_6_sensor.getValue(),self.__gripper_sensor.getValue()]
        self.__publisher_joints_encoder_data.publish(self.__joints_encoder_data)

    
    def __cmd_pos_callback(self, JointState):
        self.__target_JointState = JointState

    def step(self):
        rclpy.spin_once(self.__node, timeout_sec=0)

        self.__joint_1.setPosition(self.__target_JointState.position[0])
        self.__joint_2.setPosition(self.__target_JointState.position[1])
        self.__joint_3.setPosition(self.__target_JointState.position[2])
        self.__joint_4.setPosition(self.__target_JointState.position[3])
        self.__joint_5.setPosition(self.__target_JointState.position[4])
        self.__joint_6.setPosition(self.__target_JointState.position[5])
        self.__gripper.setPosition(self.__target_JointState.position[6])

        