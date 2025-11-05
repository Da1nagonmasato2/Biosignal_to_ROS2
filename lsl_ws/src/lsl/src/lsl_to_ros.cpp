#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <lsl_cpp.h>
#include <sstream>

class LSLBridgeNode : public rclcpp::Node {
public:
  LSLBridgeNode() : Node("lsl_bridge") {
    RCLCPP_INFO(this->get_logger(), "Resolving LSL stream...");
    auto results = lsl::resolve_stream("type", "EEG", 1, 2.0);  // 2秒待つ
    if (results.empty()) {
      RCLCPP_ERROR(this->get_logger(), "No LSL stream of type 'EEG' found!");
      return;
    }

    inlet_ = std::make_unique<lsl::stream_inlet>(results[0]);
    publisher_ = this->create_publisher<std_msgs::msg::String>("lsl_topic", 10);

    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(100),
        std::bind(&LSLBridgeNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "LSL stream connected and timer started.");
  }

private:
  void timer_callback() {
    try {
      std::vector<float> sample(8);
      double timestamp = inlet_->pull_sample(sample, 0.0);  // ノンブロッキング

      if (timestamp != 0.0) {
        std::ostringstream ss;
        ss << "Sample [";
        for (size_t i = 0; i < sample.size(); ++i) {
          ss << sample[i];
          if (i < sample.size() - 1) ss << ", ";
        }
        ss << "]  @ " << timestamp;

        auto msg = std_msgs::msg::String();
        msg.data = ss.str();
        publisher_->publish(msg);
      }
    } catch (const std::exception &e) {
      RCLCPP_ERROR(this->get_logger(), "Error reading LSL sample: %s", e.what());
    }
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::unique_ptr<lsl::stream_inlet> inlet_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LSLBridgeNode>());
  rclcpp::shutdown();
  return 0;
}

