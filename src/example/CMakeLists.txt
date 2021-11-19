cmake_minimum_required(VERSION 3.0.2)
project(example)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  utils
)

catkin_package(
#  INCLUDE_DIRS include
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

