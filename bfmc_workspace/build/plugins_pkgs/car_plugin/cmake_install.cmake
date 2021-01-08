# Install script for directory: /home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_plugin/msg" TYPE FILE FILES
    "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
    "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg"
    "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_plugin/cmake" TYPE FILE FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/build/plugins_pkgs/car_plugin/catkin_generated/installspace/car_plugin-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/devel/include/car_plugin")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/devel/share/roseus/ros/car_plugin")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/devel/share/common-lisp/ros/car_plugin")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/devel/share/gennodejs/ros/car_plugin")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/devel/lib/python2.7/dist-packages/car_plugin")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/devel/lib/python2.7/dist-packages/car_plugin")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/build/plugins_pkgs/car_plugin/catkin_generated/installspace/car_plugin.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_plugin/cmake" TYPE FILE FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/build/plugins_pkgs/car_plugin/catkin_generated/installspace/car_plugin-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_plugin/cmake" TYPE FILE FILES
    "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/build/plugins_pkgs/car_plugin/catkin_generated/installspace/car_pluginConfig.cmake"
    "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/build/plugins_pkgs/car_plugin/catkin_generated/installspace/car_pluginConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/car_plugin" TYPE FILE FILES "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/package.xml")
endif()

