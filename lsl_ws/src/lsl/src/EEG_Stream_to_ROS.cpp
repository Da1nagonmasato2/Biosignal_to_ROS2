#include <rclcpp/rclcpp.hpp>
#include <lsl_cpp.h>
#include "lsl/msg/eeg.hpp"  // 生成されるメッセージ
#include <std_msgs/msg/header.hpp>

class EEGStreamNode : public rclcpp::Node {
public:
  EEGStreamNode() : Node("EEG_Stream_to_ROS") {
    RCLCPP_INFO(this->get_logger(), "Resolving LSL stream (type='EEG')...");

    // ==== LSLストリーム検出 ====
    auto results = lsl::resolve_stream("type", "EEG", 1, 2.0);
    if (results.empty()) {
      RCLCPP_ERROR(this->get_logger(), "No LSL stream of type 'EEG' found!");
      return;
    }

    inlet_ = std::make_unique<lsl::stream_inlet>(results[0]);
    n_channels_ = inlet_->info().channel_count();

// ==== チャンネル情報を抽出 ====
auto ch_info = inlet_->info().desc().child("channels");
auto ch = ch_info.child("channel");
while (!ch.empty()) {
    std::string label = ch.child_value("label");
    if (!label.empty()) {
        channel_labels_.push_back(label);
    }
    ch = ch.next_sibling("channel");
}
if (channel_labels_.empty()) {
    for (int i = 0; i < n_channels_; ++i)
        channel_labels_.push_back("CH" + std::to_string(i + 1));
}


    publisher_ = this->create_publisher<lsl::msg::Eeg>("eeg_from_lsl", 10);

    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(10),
        std::bind(&EEGStreamNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), 
      "Connected to LSL stream '%s' (%dch)",
      inlet_->info().name().c_str(), n_channels_);
  }

private:
  void timer_callback() {
    if (!inlet_) return;

    std::vector<float> sample(n_channels_);
    double timestamp = inlet_->pull_sample(sample, 0.0); // ノンブロッキング

    if (timestamp == 0.0)
      return;

    lsl::msg::Eeg msg;
    msg.header.stamp = this->now();
    msg.channel_names = channel_labels_;
    msg.data = sample;
    msg.timestamp = timestamp;

    publisher_->publish(msg);
  }

  std::unique_ptr<lsl::stream_inlet> inlet_;
  rclcpp::Publisher<lsl::msg::Eeg>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int n_channels_{0};
  std::vector<std::string> channel_labels_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EEGStreamNode>());
  rclcpp::shutdown();
  return 0;
}

