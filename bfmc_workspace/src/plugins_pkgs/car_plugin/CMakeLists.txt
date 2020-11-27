cmake_minimum_required(VERSION 2.8.3)
project(car_plugin)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  message_generation
  roscpp
  std_msgs
)
find_package(gazebo REQUIRED)

add_message_files(
  FILES
  Key.msg
  Command.msg
  Response.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  car_plugin
)

link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${roscpp_INCLUDE_DIRS} ${std_msgs_INCLUDE_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")


add_library(car_plugin SHARED src/carlikerobot_ros_plugin.cpp src/carlikerobot.cpp)

target_link_libraries(car_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})

add_dependencies(car_plugin car_plugin_generate_messages_cpp)


catkin_package(
    CATKIN_DEPENDS
    roscpp
    gazebo_ros
    message_runtime
    std_msgs
)

