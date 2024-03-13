#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

#include "ros2webots_go_to_point_controller_model_cg.h"

using namespace std::chrono_literals;



class ROSBotWayPointTracker : public rclcpp::Node {
public:
  ROSBotWayPointTracker() : Node("rosbot_way_point_tracker") {
    publisher_ = create_publisher<geometry_msgs::msg::Twist>("/webots/rosbot/command_vel", 10);
    OdomDataSubscriber_ = this->create_subscription<nav_msgs::msg::Odometry>("/webots/rosbot/odometry", 10, 
                          std::bind(&ROSBotWayPointTracker::OdomDataSubscriber_callback, this, std::placeholders::_1));

    wayPointTrackerControllerObject.initialize();
  }

private:

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr OdomDataSubscriber_;
  rclcpp::Logger logger_ = this->get_logger();

  // Actual position data
  nav_msgs::msg::Odometry ReceivedActualLocalizationData_;

  // Desiered position data
  // TO DO --> Later we have to received them from a mission (path) planner
  double x_des = 2.; double y_des = 1.; double yaw_des = 0.;
  std::vector<double> x_des_vec = {0.0,   0.6,  1.4,    2.2,  3.2,  2.0,   0.2, 0.0};
  std::vector<double> y_des_vec = {0.0, -0.45, 0.45,  -0.45, 0.45,-0.45, -0.45, 0.0};
  int des_point_index = 0;


  // Way point tracker SDK class object
  ros2webots_go_to_point_controller_model_cg wayPointTrackerControllerObject;
  ros2webots_go_to_point_controller_model_cg::ExtU_ros2webots_go_to_point_c_T controller_input;
  ros2webots_go_to_point_controller_model_cg::ExtY_ros2webots_go_to_point_c_T controller_output;

  // Controller command to the ROSBot driver
  geometry_msgs::msg::Twist twistCommand;

  void OdomDataSubscriber_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
      ReceivedActualLocalizationData_ = *msg;
      // Set controller inputs
      controller_input.x_act    = ReceivedActualLocalizationData_.pose.pose.position.x;
      controller_input.y_act    = ReceivedActualLocalizationData_.pose.pose.position.y;
      controller_input.yaw_act  = ReceivedActualLocalizationData_.pose.pose.orientation.z;
      if(des_point_index>x_des_vec.size()){des_point_index = 0;}
      controller_input.x_des    = x_des_vec[des_point_index];    // TO DO --> Path planner node
      controller_input.y_des    = y_des_vec[des_point_index];    // TO DO --> Path planner node
      controller_input.yaw_des  = yaw_des;  // TO DO --> Path planner node

      wayPointTrackerControllerObject.setExternalInputs(&controller_input);

      // Step the controller
      wayPointTrackerControllerObject.step();

      // Get controller calculations
      controller_output = wayPointTrackerControllerObject.getExternalOutputs();

      // Control reaching to the next way point
      if(controller_output.controller_state == 0) {des_point_index++;}

      // Assign twist command
      twistCommand.linear.x   = controller_output.command_velocity;
      twistCommand.angular.z  = controller_output.command_steering_angle;
      // Info: controller_output.controller_state == 0 --> Reached to the point, == 1 --> Not reached to the point

      // Publish the control command for the ROSBot
      publisher_->publish(twistCommand);

    }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ROSBotWayPointTracker>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
