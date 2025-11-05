// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "lsl/msg/detail/eeg__rosidl_typesupport_introspection_c.h"
#include "lsl/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "lsl/msg/detail/eeg__functions.h"
#include "lsl/msg/detail/eeg__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `channel_names`
#include "rosidl_runtime_c/string_functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lsl__msg__Eeg__init(message_memory);
}

void lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_fini_function(void * message_memory)
{
  lsl__msg__Eeg__fini(message_memory);
}

size_t lsl__msg__Eeg__rosidl_typesupport_introspection_c__size_function__Eeg__channel_names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_const_function__Eeg__channel_names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_function__Eeg__channel_names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void lsl__msg__Eeg__rosidl_typesupport_introspection_c__fetch_function__Eeg__channel_names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_const_function__Eeg__channel_names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void lsl__msg__Eeg__rosidl_typesupport_introspection_c__assign_function__Eeg__channel_names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_function__Eeg__channel_names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool lsl__msg__Eeg__rosidl_typesupport_introspection_c__resize_function__Eeg__channel_names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t lsl__msg__Eeg__rosidl_typesupport_introspection_c__size_function__Eeg__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_const_function__Eeg__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_function__Eeg__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void lsl__msg__Eeg__rosidl_typesupport_introspection_c__fetch_function__Eeg__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_const_function__Eeg__data(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void lsl__msg__Eeg__rosidl_typesupport_introspection_c__assign_function__Eeg__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_function__Eeg__data(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool lsl__msg__Eeg__rosidl_typesupport_introspection_c__resize_function__Eeg__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lsl__msg__Eeg, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "channel_names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lsl__msg__Eeg, channel_names),  // bytes offset in struct
    NULL,  // default value
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__size_function__Eeg__channel_names,  // size() function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_const_function__Eeg__channel_names,  // get_const(index) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_function__Eeg__channel_names,  // get(index) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__fetch_function__Eeg__channel_names,  // fetch(index, &value) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__assign_function__Eeg__channel_names,  // assign(index, value) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__resize_function__Eeg__channel_names  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lsl__msg__Eeg, data),  // bytes offset in struct
    NULL,  // default value
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__size_function__Eeg__data,  // size() function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_const_function__Eeg__data,  // get_const(index) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__get_function__Eeg__data,  // get(index) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__fetch_function__Eeg__data,  // fetch(index, &value) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__assign_function__Eeg__data,  // assign(index, value) function pointer
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__resize_function__Eeg__data  // resize(index) function pointer
  },
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lsl__msg__Eeg, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_members = {
  "lsl__msg",  // message namespace
  "Eeg",  // message name
  4,  // number of fields
  sizeof(lsl__msg__Eeg),
  lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_member_array,  // message members
  lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_init_function,  // function to initialize message memory (memory has to be allocated)
  lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_type_support_handle = {
  0,
  &lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lsl
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lsl, msg, Eeg)() {
  lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_type_support_handle.typesupport_identifier) {
    lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lsl__msg__Eeg__rosidl_typesupport_introspection_c__Eeg_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
