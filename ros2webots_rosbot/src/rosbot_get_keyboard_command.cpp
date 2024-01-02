#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

char getch() {
  char buf = 0;
  struct termios old = {};  // Initialize all fields to their default values
  fflush(stdout);
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  return buf;
}

class KeyboardTeleopNode : public rclcpp::Node {
public:
  KeyboardTeleopNode() : Node("rosbot_get_command_keyboard") {
    publisher_ = create_publisher<geometry_msgs::msg::Twist>("/webots/rosbot/command_vel", 10);
    timer_ = create_wall_timer(50ms, std::bind(&KeyboardTeleopNode::keyboardCallback, this));
  }

private:
  void keyboardCallback() {
    char key = getch();
    geometry_msgs::msg::Twist twist;

    switch (key) {
      case 65:  // Up arrow
        twist.linear.x = 0.2;
        RCLCPP_INFO(logger_, "Up arrow has been pressed");
        break;
      case 66:  // Down arrow
        twist.linear.x = -0.2;
        RCLCPP_INFO(logger_, "Down arrow has been pressed");
        break;
      case 68:  // Left arrow
        twist.angular.z = 0.5;
        RCLCPP_INFO(logger_, "Left arrow has been pressed");
        break;
      case 67:  // Right arrow
        twist.angular.z = -0.5;
        RCLCPP_INFO(logger_, "Right arrow has been pressed");
        break;
      default:
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        break;
    }

    publisher_->publish(twist);
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Logger logger_ = this->get_logger();
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<KeyboardTeleopNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
