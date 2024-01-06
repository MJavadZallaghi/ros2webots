cmake_minimum_required(VERSION 3.8)
project(ros2webots_rosbot)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs  REQUIRED)
find_package(tf2_ros  REQUIRED)
find_package(urdf  REQUIRED)
find_package(ament_index_cpp  REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# Include Cpp "include" directory
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
add_executable(rosbot_cpp_node_test src/rosbot_cpp_node_test.cpp)
ament_target_dependencies(rosbot_cpp_node_test rclcpp std_msgs)

add_executable(rosbot_get_keyboard_command src/rosbot_get_keyboard_command.cpp)
ament_target_dependencies(rosbot_get_keyboard_command rclcpp geometry_msgs)

add_executable(rosbot_tf_publisher src/rosbot_tf_publisher.cpp)
ament_target_dependencies(rosbot_tf_publisher rclcpp tf2_ros urdf std_msgs)


# Install Cpp executables
install(TARGETS
  rosbot_cpp_node_test
  rosbot_get_keyboard_command
  rosbot_tf_publisher
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
${PROJECT_NAME}/rosbot_robot_driver.py
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
