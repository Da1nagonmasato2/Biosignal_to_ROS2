// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice

#ifndef LSL__MSG__DETAIL__EEG__BUILDER_HPP_
#define LSL__MSG__DETAIL__EEG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lsl/msg/detail/eeg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lsl
{

namespace msg
{

namespace builder
{

class Init_Eeg_timestamp
{
public:
  explicit Init_Eeg_timestamp(::lsl::msg::Eeg & msg)
  : msg_(msg)
  {}
  ::lsl::msg::Eeg timestamp(::lsl::msg::Eeg::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lsl::msg::Eeg msg_;
};

class Init_Eeg_data
{
public:
  explicit Init_Eeg_data(::lsl::msg::Eeg & msg)
  : msg_(msg)
  {}
  Init_Eeg_timestamp data(::lsl::msg::Eeg::_data_type arg)
  {
    msg_.data = std::move(arg);
    return Init_Eeg_timestamp(msg_);
  }

private:
  ::lsl::msg::Eeg msg_;
};

class Init_Eeg_channel_names
{
public:
  explicit Init_Eeg_channel_names(::lsl::msg::Eeg & msg)
  : msg_(msg)
  {}
  Init_Eeg_data channel_names(::lsl::msg::Eeg::_channel_names_type arg)
  {
    msg_.channel_names = std::move(arg);
    return Init_Eeg_data(msg_);
  }

private:
  ::lsl::msg::Eeg msg_;
};

class Init_Eeg_header
{
public:
  Init_Eeg_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Eeg_channel_names header(::lsl::msg::Eeg::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Eeg_channel_names(msg_);
  }

private:
  ::lsl::msg::Eeg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lsl::msg::Eeg>()
{
  return lsl::msg::builder::Init_Eeg_header();
}

}  // namespace lsl

#endif  // LSL__MSG__DETAIL__EEG__BUILDER_HPP_
