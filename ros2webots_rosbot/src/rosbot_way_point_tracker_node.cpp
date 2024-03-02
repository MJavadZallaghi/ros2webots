#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;



class ROSBotWayPointTracker : public rclcpp::Node {
public:
  ROSBotWayPointTracker() : Node("rosbot_way_point_tracker") {
    publisher_ = create_publisher<geometry_msgs::msg::Twist>("/webots/rosbot/command_vel", 10);
  }

private:

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Logger logger_ = this->get_logger();
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ROSBotWayPointTracker>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
