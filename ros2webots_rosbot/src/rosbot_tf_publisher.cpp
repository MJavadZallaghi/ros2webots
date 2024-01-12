// TO DO: Why graphic of the robot won't load in rviz2?

#include <urdf/model.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/parameter.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2_ros/transform_broadcaster.h>

using namespace std::chrono_literals;


class RosbotDescriptionPublisher : public rclcpp::Node {
public:
  RosbotDescriptionPublisher() : Node("rosbot_description_publisher_node") {
    urdf_path_ = ament_index_cpp::get_package_share_directory("ros2webots_rosbot") + "/resource/rosbot.urdf";
    loadURDF();
    publisher_ = this->create_publisher<std_msgs::msg::String>("robot_description_rosbot", 10);
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ = this->create_wall_timer(500ms, std::bind(&RosbotDescriptionPublisher::publishRosBotDescription, this));
    timer2_ = this->create_wall_timer(500ms, std::bind(&RosbotDescriptionPublisher::publish_transforms, this));
  }
  std::string getURDF() {
    return urdf_path_;
  }
  

private:
// Create a publisher for the robot description topic
    void publishRosBotDescription() {
        auto message = std_msgs::msg::String();
        message.data = urdf_path_;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
        }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timer2_;
    std::string urdf_path_;
    urdf::Model model;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

    void loadURDF() {
    // Load the URDF file
    if (!model.initFile(urdf_path_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to load URDF file");
        return;
    }

    // Access model information (e.g., joints, links, etc.)
    RCLCPP_INFO(this->get_logger(), "Robot name: %s", model.getName().c_str());
    }
  void publish_transforms()
  {
    // Iterate through all joints in the URDF
    for (const auto& joint : model.joints_) {
      // Get joint properties
      const std::string& parent_link_name = joint.second->parent_link_name;
      const std::string& child_link_name = joint.second->child_link_name;
      const urdf::Pose& pose = joint.second->parent_to_joint_origin_transform;

      // Create a transform message
      geometry_msgs::msg::TransformStamped transform_stamped;
      transform_stamped.header.stamp = this->get_clock()->now();
      transform_stamped.header.frame_id = parent_link_name;
      transform_stamped.child_frame_id = child_link_name;
      transform_stamped.transform.translation.x = pose.position.x;
      transform_stamped.transform.translation.y = pose.position.y;
      transform_stamped.transform.translation.z = pose.position.z;
      transform_stamped.transform.rotation.x = pose.rotation.x;
      transform_stamped.transform.rotation.y = pose.rotation.y;
      transform_stamped.transform.rotation.z = pose.rotation.z;
      transform_stamped.transform.rotation.w = pose.rotation.w;

      // Broadcast the transform
      tf_broadcaster_->sendTransform(transform_stamped);
      RCLCPP_INFO(this->get_logger(), "TF of parent link %s to child link %s has been published.", parent_link_name.c_str(), child_link_name.c_str());
    }
  }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RosbotDescriptionPublisher>();
    node->declare_parameter("rosbot_robot_description", node->getURDF());
    node->set_parameter(rclcpp::Parameter("rosbot_robot_description", node->getURDF()));
    auto parameter_value = node->get_parameter("rosbot_robot_description");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}