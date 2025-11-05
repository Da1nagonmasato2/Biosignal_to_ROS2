// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice
#include "lsl/msg/detail/eeg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `channel_names`
#include "rosidl_runtime_c/string_functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
lsl__msg__Eeg__init(lsl__msg__Eeg * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    lsl__msg__Eeg__fini(msg);
    return false;
  }
  // channel_names
  if (!rosidl_runtime_c__String__Sequence__init(&msg->channel_names, 0)) {
    lsl__msg__Eeg__fini(msg);
    return false;
  }
  // data
  if (!rosidl_runtime_c__float__Sequence__init(&msg->data, 0)) {
    lsl__msg__Eeg__fini(msg);
    return false;
  }
  // timestamp
  return true;
}

void
lsl__msg__Eeg__fini(lsl__msg__Eeg * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // channel_names
  rosidl_runtime_c__String__Sequence__fini(&msg->channel_names);
  // data
  rosidl_runtime_c__float__Sequence__fini(&msg->data);
  // timestamp
}

bool
lsl__msg__Eeg__are_equal(const lsl__msg__Eeg * lhs, const lsl__msg__Eeg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // channel_names
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->channel_names), &(rhs->channel_names)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  return true;
}

bool
lsl__msg__Eeg__copy(
  const lsl__msg__Eeg * input,
  lsl__msg__Eeg * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // channel_names
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->channel_names), &(output->channel_names)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  return true;
}

lsl__msg__Eeg *
lsl__msg__Eeg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lsl__msg__Eeg * msg = (lsl__msg__Eeg *)allocator.allocate(sizeof(lsl__msg__Eeg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lsl__msg__Eeg));
  bool success = lsl__msg__Eeg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lsl__msg__Eeg__destroy(lsl__msg__Eeg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lsl__msg__Eeg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lsl__msg__Eeg__Sequence__init(lsl__msg__Eeg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lsl__msg__Eeg * data = NULL;

  if (size) {
    data = (lsl__msg__Eeg *)allocator.zero_allocate(size, sizeof(lsl__msg__Eeg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lsl__msg__Eeg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lsl__msg__Eeg__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
lsl__msg__Eeg__Sequence__fini(lsl__msg__Eeg__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      lsl__msg__Eeg__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

lsl__msg__Eeg__Sequence *
lsl__msg__Eeg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lsl__msg__Eeg__Sequence * array = (lsl__msg__Eeg__Sequence *)allocator.allocate(sizeof(lsl__msg__Eeg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lsl__msg__Eeg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lsl__msg__Eeg__Sequence__destroy(lsl__msg__Eeg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lsl__msg__Eeg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lsl__msg__Eeg__Sequence__are_equal(const lsl__msg__Eeg__Sequence * lhs, const lsl__msg__Eeg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lsl__msg__Eeg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lsl__msg__Eeg__Sequence__copy(
  const lsl__msg__Eeg__Sequence * input,
  lsl__msg__Eeg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lsl__msg__Eeg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lsl__msg__Eeg * data =
      (lsl__msg__Eeg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lsl__msg__Eeg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lsl__msg__Eeg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lsl__msg__Eeg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
