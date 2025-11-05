// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice

#ifndef LSL__MSG__DETAIL__EEG__TRAITS_HPP_
#define LSL__MSG__DETAIL__EEG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lsl/msg/detail/eeg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace lsl
{

namespace msg
{

inline void to_flow_style_yaml(
  const Eeg & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: channel_names
  {
    if (msg.channel_names.size() == 0) {
      out << "channel_names: []";
    } else {
      out << "channel_names: [";
      size_t pending_items = msg.channel_names.size();
      for (auto item : msg.channel_names) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Eeg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: channel_names
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.channel_names.size() == 0) {
      out << "channel_names: []\n";
    } else {
      out << "channel_names:\n";
      for (auto item : msg.channel_names) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Eeg & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace lsl

namespace rosidl_generator_traits
{

[[deprecated("use lsl::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lsl::msg::Eeg & msg,
  std::ostream & out, size_t indentation = 0)
{
  lsl::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lsl::msg::to_yaml() instead")]]
inline std::string to_yaml(const lsl::msg::Eeg & msg)
{
  return lsl::msg::to_yaml(msg);
}

template<>
inline const char * data_type<lsl::msg::Eeg>()
{
  return "lsl::msg::Eeg";
}

template<>
inline const char * name<lsl::msg::Eeg>()
{
  return "lsl/msg/Eeg";
}

template<>
struct has_fixed_size<lsl::msg::Eeg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lsl::msg::Eeg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lsl::msg::Eeg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LSL__MSG__DETAIL__EEG__TRAITS_HPP_
