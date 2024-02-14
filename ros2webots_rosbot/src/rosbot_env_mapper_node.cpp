// TO DO: Implement LaserScan/PointCloud2 subscription mechanism [Select one of them]

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include "ros2webots_rosbot/rosbot_localization_node.hpp"

// Localization SDK main header
#include "laser_env_mapper.hpp"

#include "rclcpp/rclcpp.hpp"

#include "nav_msgs/msg/odometry.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      subscriberOdom_ = this->create_subscription<nav_msgs::msg::Odometry>("/webots/rosbot/odometry", 10, std::bind(&MinimalPublisher::subscriberOdom_callback, this, std::placeholders::_1));
      publisherGridMapData_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("/webots/rosbot/occupancy_grid_map", 10);
      // Initialize map object
    
    }

  private:

    void subscriberOdom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
      OdomMessageData = *msg;
    }

    double getFullTime(const uint32_t MsgHeaderSec, const uint32_t MsgHeaderNSec) {
      double timeWithFullRes;
      timeWithFullRes = MsgHeaderSec + MsgHeaderNSec* 1e-9;
      return timeWithFullRes;
    }

    // Environment mapping SDK object
    LaserEnvMapper map_env_laser;

    // Odom data subcriber
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscriberOdom_;

    // Odom sub message data
    nav_msgs::msg::Odometry OdomMessageData;

    // Map data publisher
    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr publisherGridMapData_;

    // Map pub message data
    nav_msgs::msg::OccupancyGrid OccupancyGridMapData;

    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
