cmake_minimum_required(VERSION 3.0.2)
project(startup_package)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(catkin REQUIRED COMPONENTS
	sensor_msgs
	cv_bridge
	rospy
	std_msgs
)

find_package(OpenCV REQUIRED)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

