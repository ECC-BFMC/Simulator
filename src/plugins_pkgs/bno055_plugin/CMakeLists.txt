cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(bno055_plugin)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  roscpp
  utils
)

find_package(gazebo REQUIRED)

generate_messages(DEPENDENCIES)

catkin_package(CATKIN_DEPENDS 
  gazebo_ros
  roscpp
  utils
)

link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(bno055_plugin SHARED src/bno055_plugin.cpp include/bno055_plugin.hpp)

target_link_libraries(bno055_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})
