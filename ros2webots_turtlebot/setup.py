# Lunch file import
import os
from glob import glob

from setuptools import find_packages, setup

package_name = 'ros2webots_turtlebot'
data_files = []
data_files.append(('share/ament_index/resource_index/packages', [
    'resource/' + package_name
]))
data_files.append(('share/' + package_name + '/launch', [
    'launch/test_launch.py',
    'launch/turtlebot_world_launch.py',
]))
data_files.append(('share/' + package_name + '/worlds', [
    'worlds/world_roboticknowledge.wbt',
]))
# data_files.append(('share/' + package_name + '/protos', [
#     'protos/LegoTallInterval.proto',
# ]))
# data_files.append(('share/' + package_name + '/resource', [
#     'resource/all.rviz',
# ]))
data_files.append(('share/' + package_name, [
    'package.xml'
]))

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=data_files,
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='mjavadzallaghi',
    maintainer_email='mohammadjavadzallaghi@gmail.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
