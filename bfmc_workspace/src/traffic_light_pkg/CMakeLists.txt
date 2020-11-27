cmake_minimum_required(VERSION 3.0.2)
project(traffic_light_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
 add_message_files(
   FILES
   traffic_light.msg
 )

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

 catkin_install_python(PROGRAMS src/tl_talker.py src/tl_listener.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )
