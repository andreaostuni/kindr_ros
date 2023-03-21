cmake_minimum_required(VERSION 3.5.1)
project(kindr_msgs)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Woverloaded-virtual)
endif()

## Find packages

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
set(msg_files msg/VectorAtPosition.msg)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES builtin_interfaces std_msgs geometry_msgs
)

ament_export_dependencies(rosidl_default_runtime std_msgs geometry_msgs)

ament_package()
