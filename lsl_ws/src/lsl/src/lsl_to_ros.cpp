#include <rclcpp/rclcpp.hpp>
#include <lsl_cpp.h>
#include "lsl/msg/eeg.hpp"

class EMGFromEEGNode : public rclcpp::Node {
public:
  EMGFromEEGNode() : Node("emg_from_eeg") {
    RCLCPP_INFO(this->get_logger(), "Resolving LSL EMG stream for EMG...");

    auto results = lsl::resolve_stream("type", "EMG", 1, 2.0);
    if (results.empty()) {
      RCLCPP_ERROR(this->get_logger(), "No LSL EMG stream found!");
      return;
    }

    inlet_ = std::make_unique<lsl::stream_inlet>(results[0]);
    n_channels_ = inlet_->info().channel_count();
    if (n_channels_ < 1) {
        RCLCPP_ERROR(this->get_logger(), "EMG stream has no channels!");
        return;
    }

    // チャンネルラベルを取得
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
        channel_labels_.push_back("CH0");
    }

    emg_pub_ = this->create_publisher<lsl::msg::Eeg>("emg_from_eeg", 10);

    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(10),
        std::bind(&EMGFromEEGNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "Connected to EEG stream, publishing channel 0 as EMG.");
  }

private:
  void timer_callback() {
    if (!inlet_) return;

    std::vector<float> sample(n_channels_);
    double timestamp = inlet_->pull_sample(sample, 0.0); // ノンブロッキング
    if (timestamp == 0.0) return;

    lsl::msg::Eeg msg;
    msg.header.stamp = this->now();       // ROS タイムスタンプ
    msg.channel_names = {channel_labels_[0]}; // 1チャンネルだけ
    msg.data = {sample[0]};                // 1チャンネルだけ
    msg.timestamp = timestamp;             // LSL タイムスタンプ（任意）

    emg_pub_->publish(msg);
  }

  std::unique_ptr<lsl::stream_inlet> inlet_;
  rclcpp::Publisher<lsl::msg::Eeg>::SharedPtr emg_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  int n_channels_{0};
  std::vector<std::string> channel_labels_;
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EMGFromEEGNode>());
  rclcpp::shutdown();
  return 0;
}

