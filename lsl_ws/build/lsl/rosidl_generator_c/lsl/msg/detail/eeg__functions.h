// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from lsl:msg/Eeg.idl
// generated code does not contain a copyright notice

#ifndef LSL__MSG__DETAIL__EEG__FUNCTIONS_H_
#define LSL__MSG__DETAIL__EEG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "lsl/msg/rosidl_generator_c__visibility_control.h"

#include "lsl/msg/detail/eeg__struct.h"

/// Initialize msg/Eeg message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * lsl__msg__Eeg
 * )) before or use
 * lsl__msg__Eeg__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
bool
lsl__msg__Eeg__init(lsl__msg__Eeg * msg);

/// Finalize msg/Eeg message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
void
lsl__msg__Eeg__fini(lsl__msg__Eeg * msg);

/// Create msg/Eeg message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * lsl__msg__Eeg__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
lsl__msg__Eeg *
lsl__msg__Eeg__create();

/// Destroy msg/Eeg message.
/**
 * It calls
 * lsl__msg__Eeg__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
void
lsl__msg__Eeg__destroy(lsl__msg__Eeg * msg);

/// Check for msg/Eeg message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
bool
lsl__msg__Eeg__are_equal(const lsl__msg__Eeg * lhs, const lsl__msg__Eeg * rhs);

/// Copy a msg/Eeg message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
bool
lsl__msg__Eeg__copy(
  const lsl__msg__Eeg * input,
  lsl__msg__Eeg * output);

/// Initialize array of msg/Eeg messages.
/**
 * It allocates the memory for the number of elements and calls
 * lsl__msg__Eeg__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
bool
lsl__msg__Eeg__Sequence__init(lsl__msg__Eeg__Sequence * array, size_t size);

/// Finalize array of msg/Eeg messages.
/**
 * It calls
 * lsl__msg__Eeg__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
void
lsl__msg__Eeg__Sequence__fini(lsl__msg__Eeg__Sequence * array);

/// Create array of msg/Eeg messages.
/**
 * It allocates the memory for the array and calls
 * lsl__msg__Eeg__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
lsl__msg__Eeg__Sequence *
lsl__msg__Eeg__Sequence__create(size_t size);

/// Destroy array of msg/Eeg messages.
/**
 * It calls
 * lsl__msg__Eeg__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
void
lsl__msg__Eeg__Sequence__destroy(lsl__msg__Eeg__Sequence * array);

/// Check for msg/Eeg message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
bool
lsl__msg__Eeg__Sequence__are_equal(const lsl__msg__Eeg__Sequence * lhs, const lsl__msg__Eeg__Sequence * rhs);

/// Copy an array of msg/Eeg messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_lsl
bool
lsl__msg__Eeg__Sequence__copy(
  const lsl__msg__Eeg__Sequence * input,
  lsl__msg__Eeg__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // LSL__MSG__DETAIL__EEG__FUNCTIONS_H_
