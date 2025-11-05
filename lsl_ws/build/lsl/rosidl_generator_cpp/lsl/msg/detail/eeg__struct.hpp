// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice

#ifndef LSL__MSG__DETAIL__EEG__STRUCT_HPP_
#define LSL__MSG__DETAIL__EEG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__lsl__msg__Eeg __attribute__((deprecated))
#else
# define DEPRECATED__lsl__msg__Eeg __declspec(deprecated)
#endif

namespace lsl
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Eeg_
{
  using Type = Eeg_<ContainerAllocator>;

  explicit Eeg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0.0;
    }
  }

  explicit Eeg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _channel_names_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _channel_names_type channel_names;
  using _data_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _data_type data;
  using _timestamp_type =
    double;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__channel_names(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->channel_names = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->data = _arg;
    return *this;
  }
  Type & set__timestamp(
    const double & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lsl::msg::Eeg_<ContainerAllocator> *;
  using ConstRawPtr =
    const lsl::msg::Eeg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lsl::msg::Eeg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lsl::msg::Eeg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lsl::msg::Eeg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lsl::msg::Eeg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lsl::msg::Eeg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lsl::msg::Eeg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lsl::msg::Eeg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lsl::msg::Eeg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lsl__msg__Eeg
    std::shared_ptr<lsl::msg::Eeg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lsl__msg__Eeg
    std::shared_ptr<lsl::msg::Eeg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Eeg_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->channel_names != other.channel_names) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const Eeg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Eeg_

// alias to use template instance with default allocator
using Eeg =
  lsl::msg::Eeg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lsl

#endif  // LSL__MSG__DETAIL__EEG__STRUCT_HPP_
