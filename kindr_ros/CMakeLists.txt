cmake_minimum_required(VERSION 3.5.1)
project(kindr_ros)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)

# Attempt to find catkinized kindr
find_package(kindr QUIET)
if(NOT kindr_FOUND)
  # Attempt to find package-based kindr
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(kindr kindr REQUIRED)
endif()

find_package(Eigen3 QUIET NO_MODULE)
if(NOT Eigen3_FOUND)
  find_package(Eigen3 REQUIRED)
endif()

ament_export_dependencies(geometry_msgs tf2 Eigen3 kindr)
ament_export_include_directories(include ${EIGEN3_INCLUDE_DIR})
ament_export_libraries(kindr_ros)

include_directories(include)
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${kindr_INCLUDE_DIRS})

#############
## Testing ##
#############

# if(CATKIN_ENABLE_TESTING)
#   catkin_add_gtest(${PROJECT_NAME}-test
#     test/test_main.cpp
#     test/RosGeometryMsgPhysicalQuantitiesTest.cpp
#     test/RosGeometryMsgRotationTest.cpp
#     test/RosGeometryMsgPoseTest.cpp
#     test/RosTfPoseTest.cpp
#     test/TfConventionTest.cpp
#     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
#     )
#   if(TARGET ${PROJECT_NAME}-test)
#     target_link_libraries(${PROJECT_NAME}-test ${catkin_LIBRARIES})
#     find_package(cmake_code_coverage QUIET)
#     if(cmake_code_coverage_FOUND)
#       add_gtest_coverage(TEST_BUILD_TARGETS ${PROJECT_NAME}-test)
#     endif(cmake_code_coverage_FOUND)
#   endif()
# endif()

if (BUILD_TESTING)
  message("Building test for " ${PROJECT_NAME})
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME}-test 
    test/test_main.cpp
    test/RosGeometryMsgPhysicalQuantitiesTest.cpp
    test/RosGeometryMsgRotationTest.cpp
    test/RosGeometryMsgPoseTest.cpp
    test/RosTfPoseTest.cpp
    test/TfConventionTest.cpp
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    )
  if(TARGET ${PROJECT_NAME}-test)
    ament_target_dependencies(${PROJECT_NAME}-test
      geometry_msgs
      tf2
      Eigen3
      kindr)
  endif()
endif()

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
  )

ament_package()