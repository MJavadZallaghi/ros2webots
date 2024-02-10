
# ros2webots

Simulation on Webots, Development with ROS2!

In ```ros2webots``` repo, we are creating simulated robots and environments in Webots, that are controlled by ROS2. The whole simulation (Webots world setup + ROS2-based software of the robot) is done in one ROS2 package.

Currently the repo hosts two ROS2 packages:

- ```ros2webots_rosbot```: A rosbot is used in this world. The future development and simulation feature improvement will be mainly done in this package, as rosbot has many sensors like Camera, Lidar, and IMU; Also, the ```ros2webots_rosbot``` package building is done by ```ament_cmake```, that makes it easier for C++ based development.
![alt world of rosbot](https://github.com/MJavadZallaghi/ros2webots/blob/main/ros2webots_rosbot/worlds/.world_roboticknowledge.jpg)
- ```ros2webots_turtlebot```: The world has a turtlebot, and package has been build using ```ament_python``` for initial ROS2+Webots interface setup tests.



## Demo
- ROSbot localization node
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/x2v0zY_rH44/0.jpg)](https://www.youtube.com/watch?v=x2v0zY_rH44)
- Controlling the rosbot by keyboard
![alt demo of robot controlled by keyboard](https://github.com/MJavadZallaghi/ros2webots/blob/main/media/ros2webots_rosbot_demo_keyboard_control.gif)


## Installation
### Install directly
I assume you have installed Ubuntu 22.04 as OS or installed on Windows WSL2.

1. Install [ROS2 iron](https://docs.ros.org/en/iron/Installation.html)
2. Install [Webots](https://cyberbotics.com/doc/guide/installing-webots). If you are working on WSL2, then you can install Webots on windows as ```webots_ros2``` package can find your installation by a ```WEBOTS_HOME``` variable. Don't worry, eveything is explain the the reference of step 3.
3. Install [```webots_ros2```](https://docs.ros.org/en/iron/Tutorials/Advanced/Simulators/Webots/Simulation-Webots.html) package.
4. Clone the repo whereever you want:
   ```
   git clone https://github.com/MJavadZallaghi/ros2webots.git
   ```
5. change directory to the workspace of the cloned package:
   ```
   cd ros2webots
   ```
6. Source your ros2 installation:
   ```
    source /opt/ros/iron/setup.bash
   ```
7. Build the package.
   ```
   colcon build
   ```
8. Source ```ros2webots``` installed packages:
   ```
   source install/setup.bash
   ```
8. Check the installation:
```
ros2 pkg list |grep ros2webots
```
You must see this package: ```ros2webots_rosbot```
### Install using Docker
Docker image of the ros2webots package is under construction!
    
## Run the simulations
- sim 1: rosbot controlled by the keyboard arrows
1. Run the rosbot wprld in terminal 1:
   ```
   ros2 launch ros2webots_rosbot rosbot_world_launch.py
   ```
2. Run the keboard commanding node in terminal 2:
   ```
   ros2 run ros2webots_rosbot rosbot_get_keyboard_command
   ```
3. Command the rosbot by your arrows from second terminal.


## Roadmap
- Visualized the rosbot using rviz2 with it's frames, sensor data, etc.
- Implment IMU based locallization fir the rosbot and visualize its path using rviz.
- Implement KF for the IMU data and increase the localization accuracy.
- Add SLAM to the rosbot for environment mapping.


## Support and Feedback
For any support and feedback, email MohammadJavadZallaghi@gmail.com or use [issues](https://github.com/MJavadZallaghi/ros2webots/issues) section of this repo.


## License
[MIT](https://choosealicense.com/licenses/mit/)


## Authors
- [@MJavadZallaghi](https://www.github.com/MJavadZallaghi)


## Acknowledgements
 - ```ros2webots``` is created based on the Webots and ROS2 interface, that is possible by using ```webots_ros2``` package.```webots_ros2``` is a package that provides the necessary interfaces to simulate a robot in the Webots open-source 3D robots simulator.  (https://github.com/cyberbotics/webots_ros2)

