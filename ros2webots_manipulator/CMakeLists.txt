cmake_minimum_required(VERSION 3.8)
project(ros2webots_manipulator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs  REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2_ros  REQUIRED)
find_package(urdf  REQUIRED)
find_package(ament_index_cpp  REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

include_directories(include)


install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)
install(DIRECTORY
  worlds
  DESTINATION share/${PROJECT_NAME}/
)
install(DIRECTORY
  resource
  DESTINATION share/${PROJECT_NAME}/
)

# Create Cpp executable
add_executable(ned_node_moveit2 src/ned_node_moveit2.cpp)
ament_target_dependencies(ned_node_moveit2 rclcpp std_msgs moveit_ros_planning_interface)

# Install Cpp executables
install(TARGETS
  ned_node_moveit2
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
${PROJECT_NAME}/ned_robot_driver.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
