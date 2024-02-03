#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "ros2webots_rosbot/rosbot_localization_node.hpp"

// Localization SDK main header
#include "ros2webots_localization_model_cg.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      publisherOdomData_ = this->create_publisher<nav_msgs::msg::Odometry>("ros2/rosbot/odometry", 10);
      timerOdomDataPub_ = this->create_wall_timer(50ms, std::bind(&MinimalPublisher::timerOdomDataPub_callback, this));

      subscriberIMU_ = this->create_subscription<sensor_msgs::msg::Imu>("/webots/rosbot/imu", 10, std::bind(&MinimalPublisher::subscriberIMU_callback, this, std::placeholders::_1));
      subscriberWheelsData_ = this->create_subscription<sensor_msgs::msg::JointState>("/webots/rosbot/odom/wheels_encoder_data", 10, std::bind(&MinimalPublisher::subscriberWheelsData_callback, this, std::placeholders::_1));
      // Initialized Localozition SDK object
      localization_sdk_obj_.initialize();
    }

  private:

    void timerOdomDataPub_callback() {
      RunLocalizationProcess();
      auto message = nav_msgs::msg::Odometry();
      auto current_time = std::chrono::system_clock::now();
      auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(current_time.time_since_epoch());
      message.header.stamp.sec = static_cast<uint32_t>(timestamp.count());
      message.header.stamp.nanosec = static_cast<uint32_t>((current_time.time_since_epoch() - timestamp).count());
      message.pose.pose.position.x = 1.3;
      publisherOdomData_->publish(message);
    }

    void RunLocalizationProcess() {
      // Set inputs
      localization_input_data.imu_orientation_vector[0] = Imu_data_received.orientation.x;
      localization_input_data.imu_orientation_vector[1] = Imu_data_received.orientation.y;
      localization_input_data.imu_orientation_vector[2] = Imu_data_received.orientation.z;
      localization_input_data.imu_orientation_vector[3] = Imu_data_received.orientation.w;
      localization_input_data.imu_angular_velocity_vector[0] = Imu_data_received.angular_velocity.x;
      localization_input_data.imu_angular_velocity_vector[1] = Imu_data_received.angular_velocity.y;
      localization_input_data.imu_angular_velocity_vector[2] = Imu_data_received.angular_velocity.z;
      localization_input_data.imu_linear_acceleration_vector[0] = Imu_data_received.linear_acceleration.x;
      localization_input_data.imu_linear_acceleration_vector[1] = Imu_data_received.linear_acceleration.y;
      localization_input_data.imu_linear_acceleration_vector[2] = Imu_data_received.linear_acceleration.z;
      localization_input_data.fl_wheel_pose = Wheels_encoder_data_received.position[0];
      localization_input_data.fr_wheel_pose = Wheels_encoder_data_received.position[1];
      localization_input_data.rl_wheel_pose = Wheels_encoder_data_received.position[2];
      localization_input_data.rr_wheel_pose = Wheels_encoder_data_received.position[3];
      localization_sdk_obj_.setExternalInputs(&localization_input_data);
      // Do localization
      localization_sdk_obj_.step();
      // Get outputs
      localization_output_data = localization_sdk_obj_.getExternalOutputs();
    }

    void subscriberIMU_callback(const sensor_msgs::msg::Imu::SharedPtr msg) {
      // RCLCPP_INFO(this->get_logger(), "Received IMU data");
      Imu_data_received = *msg;
      // RCLCPP_INFO(this->get_logger(), "IMU orientation w:%f", Imu_data_received.orientation.w);
    }

    void subscriberWheelsData_callback(const sensor_msgs::msg::JointState::SharedPtr msg) {
      Wheels_encoder_data_received = *msg;
    }

    // Odom pablisher timer
    rclcpp::TimerBase::SharedPtr timerOdomDataPub_;
    // Odom publisher
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisherOdomData_;
    // IMU data subcriber
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscriberIMU_;
    // Wheel encoders data subcriber
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscriberWheelsData_;

    size_t count_;

    // Create Localizition SDK object
    ros2webots_localization_model_cg localization_sdk_obj_;

    // Localization input data struct
    ros2webots_localization_model_cg::ExtU_ros2webots_localization__T localization_input_data;

    // Localization output data struct
    ros2webots_localization_model_cg::ExtY_ros2webots_localization__T localization_output_data;

    // IMU data struct (received)
    sensor_msgs::msg::Imu Imu_data_received;

    // Wheels encoder data struct (received)
    sensor_msgs::msg::JointState Wheels_encoder_data_received;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
