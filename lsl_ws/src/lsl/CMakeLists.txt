cmake_minimum_required(VERSION 3.8)
project(lsl)

# ===== 基本依存 =====
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ===== LSL ヘッダとライブラリ =====
set(LSL_INCLUDE_DIR "/usr/local/include")
set(LSL_LIB "/usr/local/lib/liblsl.so")
include_directories(${LSL_INCLUDE_DIR})

# ===== メッセージ生成 =====
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Eeg.msg"
  DEPENDENCIES std_msgs
)

ament_export_dependencies(rosidl_default_runtime)

# ===== ノード追加 =====
add_executable(lsl_node src/lsl_to_ros.cpp)
ament_target_dependencies(lsl_node rclcpp std_msgs)
target_link_libraries(lsl_node ${LSL_LIB})


add_executable(EEG_Stream_to_ROS src/EEG_Stream_to_ROS.cpp)
ament_target_dependencies(EEG_Stream_to_ROS rclcpp std_msgs) # ${PROJECT_NAME} を削除
target_link_libraries(EEG_Stream_to_ROS ${LSL_LIB})

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(EEG_Stream_to_ROS "${cpp_typesupport_target}") 


# ===== インストール =====
install(TARGETS
  lsl_node
  EEG_Stream_to_ROS
  DESTINATION lib/${PROJECT_NAME})

ament_package()

