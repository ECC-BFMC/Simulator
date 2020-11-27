cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(pedestrian_object_plugin)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp gazebo_ros)

find_package(gazebo REQUIRED)

link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(${GAZEBO_INCLUDE_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

add_library(pedestrian_object_plugin SHARED
 src/geometric_point.cpp
 src/pedestrian_object_plugin.cpp 
 include/geometric_point.h
 include/pedestrian_object_plugin.h
)

target_link_libraries(pedestrian_object_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})


