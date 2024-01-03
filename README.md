
# ros2webots

Simulation on Webots, Development with ROS2!

In ```ros2webots``` repo, we are creating simulated robots and environments in Webots, that are controlled by ROS2. The whole simulation (Webots world setup + ROS2-based software of the robot) is done in one ROS2 package.

Currently the repo hosts two ROS2 packages:

- ```ros2webots_rosbot```: A rosbot is used in this world. The future development and simulation feature improvement will be mainly done in this package, as rosbot has many sensors like Camera, Lidar, and IMU; Also, the ```ros2webots_rosbot``` package building is done by ```ament_cmake```, that makes it easier for C++ based development.
![alt world of rosbot](https://github.com/MJavadZallaghi/ros2webots/blob/main/ros2webots_rosbot/worlds/.world_roboticknowledge.jpg)
- ```ros2webots_turtlebot```: The world has a turtlebot, and package has been build using ```ament_python``` for initial ROS2+Webots interface setup tests.



## Demo

Insert gif or link to demo

- Controlling the rosbot by keyboard

TO DO


## Installation
### Install directly
I assume you have Ubuntu 22.04 installed as OS or installed on WSL2.

1. Install [ROS2 iron](https://docs.ros.org/en/iron/Installation.html)

2. Install [Webots](https://cyberbotics.com/doc/guide/installing-webots)

3. Install [```webots_ros2``` package](https://docs.ros.org/en/iron/Tutorials/Advanced/Simulators/Webots/Simulation-Webots.html)

4. 

Install my-project with npm

```bash
  npm install my-project
  cd my-project
```
### Install using Docker
Docker image of the ros2webots package is under construction!
    
## Usage/Examples

TO DO

```javascript
import Component from 'my-project'

function App() {
  return <Component />
}
```


## Roadmap

- Add arrow-based control for rosbot of ```ros2webots_rosbot``` package.

- Update and Complete file of readme ASAP.

- Determine change in position of the rosbot and visualize its path using rviz.


## Support and Feedback

For any support and feedback, email MohammadJavadZallaghi@gmail.com or use [issues](https://github.com/MJavadZallaghi/ros2webots/issues) section of this repo.


## License

[MIT](https://choosealicense.com/licenses/mit/)


## Authors

- [@MJavadZallaghi](https://www.github.com/MJavadZallaghi)


## Acknowledgements

 - ```ros2webots``` is created based on the Webots and ROS2 interface, that is possible by using ```webots_ros2``` package.```webots_ros2``` is a package that provides the necessary interfaces to simulate a robot in the Webots open-source 3D robots simulator.  (https://github.com/cyberbotics/webots_ros2)

