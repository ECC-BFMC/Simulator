cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(traffic_light_plugin)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  traffic_light_pkg
  roscpp
  std_msgs
)

find_package(gazebo REQUIRED)

link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(traffic_light_plugin SHARED src/traffic_light_plugin.cpp include/traffic_light_plugin.hpp)

target_link_libraries(traffic_light_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})

add_dependencies(traffic_light_plugin traffic_light_pkg_generate_messages_cpp)

catkin_package(
  CATKIN_DEPENDS
  roscpp
  gazebo_ros
  traffic_light_pkg
)
