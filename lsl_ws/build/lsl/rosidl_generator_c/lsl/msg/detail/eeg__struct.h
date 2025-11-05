// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice

#ifndef LSL__MSG__DETAIL__EEG__STRUCT_H_
#define LSL__MSG__DETAIL__EEG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'channel_names'
#include "rosidl_runtime_c/string.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Eeg in the package lsl.
typedef struct lsl__msg__Eeg
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String__Sequence channel_names;
  rosidl_runtime_c__float__Sequence data;
  double timestamp;
} lsl__msg__Eeg;

// Struct for a sequence of lsl__msg__Eeg.
typedef struct lsl__msg__Eeg__Sequence
{
  lsl__msg__Eeg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lsl__msg__Eeg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LSL__MSG__DETAIL__EEG__STRUCT_H_
