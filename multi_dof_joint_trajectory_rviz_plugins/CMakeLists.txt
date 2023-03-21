cmake_minimum_required(VERSION 3.5.1)
project(multi_dof_joint_trajectory_rviz_plugins)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Qt5 boilerplate options from http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Test Concurrent)
find_package(rviz_common REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(std_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)

include_directories(
  include
)

## Here we specify which header files need to be run through "moc",
## Qt's meta-object compiler.
set(multi_dof_joint_trajectory_rviz_plugins_headers_to_moc
  include/multi_dof_joint_trajectory_rviz_plugins/MultiDOFJointTrajectoryDisplay.hpp
  include/multi_dof_joint_trajectory_rviz_plugins/MultiDOFJointTrajectoryPointConnectionVisual.hpp
  include/multi_dof_joint_trajectory_rviz_plugins/MultiDOFJointTrajectoryPointVisual.hpp
)

set(library_name ${PROJECT_NAME})

## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)


set(multi_dof_joint_trajectory_rviz_plugins_SRCS
  src/MultiDOFJointTrajectoryDisplay.cpp
  src/MultiDOFJointTrajectoryPointConnectionVisual.cpp
  src/MultiDOFJointTrajectoryPointVisual.cpp
)

set(dependencies
  ament_cmake
  pluginlib
  Qt5
  rviz_common
  rviz_default_plugins
  rviz_ogre_vendor
  rviz_rendering
  trajectory_msgs
  )

ament_target_dependencies(${library_name}
  ${dependencies}
)

target_include_directories(${library_name} PUBLIC
  ${Qt5Widgets_INCLUDE_DIRS}
  ${OGRE_INCLUDE_DIRS}
)

target_link_libraries(${library_name}
  rviz_common::rviz_common
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
# TODO: Make this specific to this project (not rviz default plugins)
target_compile_definitions(${library_name} PRIVATE "RVIZ_DEFAULT_PLUGINS_BUILDING_LIBRARY")

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

## Install rules

install(
  TARGETS ${library_name}
  EXPORT ${library_name}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY include/
  DESTINATION include/
)

install(DIRECTORY icons
  DESTINATION share/${PROJECT_NAME}
)

##########
## Test ##
##########
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME}_test
    test/EmptyTests.cpp
  )
  ament_target_dependencies(${PROJECT_NAME}_test
    ${dependencies}
  )
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_targets(${library_name} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  Qt5
  rviz_common
  trajectory_msgs
)

ament_package()
