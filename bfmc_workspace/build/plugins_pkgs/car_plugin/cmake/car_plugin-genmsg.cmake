# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "car_plugin: 3 messages, 0 services")

set(MSG_I_FLAGS "-Icar_plugin:/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Icar_plugin:/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(car_plugin_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" NAME_WE)
add_custom_target(_car_plugin_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_plugin" "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" "car_plugin/Key"
)

get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" NAME_WE)
add_custom_target(_car_plugin_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_plugin" "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" ""
)

get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" NAME_WE)
add_custom_target(_car_plugin_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_plugin" "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" "car_plugin/Key"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_plugin
)
_generate_msg_cpp(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_plugin
)
_generate_msg_cpp(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_plugin
)

### Generating Services

### Generating Module File
_generate_module_cpp(car_plugin
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_plugin
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(car_plugin_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(car_plugin_generate_messages car_plugin_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_cpp _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_cpp _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_cpp _car_plugin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_plugin_gencpp)
add_dependencies(car_plugin_gencpp car_plugin_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_plugin_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_plugin
)
_generate_msg_eus(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_plugin
)
_generate_msg_eus(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_plugin
)

### Generating Services

### Generating Module File
_generate_module_eus(car_plugin
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_plugin
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(car_plugin_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(car_plugin_generate_messages car_plugin_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_eus _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_eus _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_eus _car_plugin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_plugin_geneus)
add_dependencies(car_plugin_geneus car_plugin_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_plugin_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_plugin
)
_generate_msg_lisp(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_plugin
)
_generate_msg_lisp(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_plugin
)

### Generating Services

### Generating Module File
_generate_module_lisp(car_plugin
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_plugin
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(car_plugin_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(car_plugin_generate_messages car_plugin_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_lisp _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_lisp _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_lisp _car_plugin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_plugin_genlisp)
add_dependencies(car_plugin_genlisp car_plugin_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_plugin_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_plugin
)
_generate_msg_nodejs(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_plugin
)
_generate_msg_nodejs(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_plugin
)

### Generating Services

### Generating Module File
_generate_module_nodejs(car_plugin
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_plugin
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(car_plugin_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(car_plugin_generate_messages car_plugin_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_nodejs _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_nodejs _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_nodejs _car_plugin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_plugin_gennodejs)
add_dependencies(car_plugin_gennodejs car_plugin_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_plugin_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin
)
_generate_msg_py(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin
)
_generate_msg_py(car_plugin
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg"
  "${MSG_I_FLAGS}"
  "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin
)

### Generating Services

### Generating Module File
_generate_module_py(car_plugin
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(car_plugin_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(car_plugin_generate_messages car_plugin_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Response.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_py _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Key.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_py _car_plugin_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/rares/Documents/BFMC_Simulator/bfmc_workspace/src/plugins_pkgs/car_plugin/msg/Command.msg" NAME_WE)
add_dependencies(car_plugin_generate_messages_py _car_plugin_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_plugin_genpy)
add_dependencies(car_plugin_genpy car_plugin_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_plugin_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_plugin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_plugin
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(car_plugin_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET car_plugin_generate_messages_cpp)
  add_dependencies(car_plugin_generate_messages_cpp car_plugin_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_plugin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/car_plugin
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(car_plugin_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET car_plugin_generate_messages_eus)
  add_dependencies(car_plugin_generate_messages_eus car_plugin_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_plugin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_plugin
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(car_plugin_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET car_plugin_generate_messages_lisp)
  add_dependencies(car_plugin_generate_messages_lisp car_plugin_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_plugin)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/car_plugin
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(car_plugin_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET car_plugin_generate_messages_nodejs)
  add_dependencies(car_plugin_generate_messages_nodejs car_plugin_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_plugin
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(car_plugin_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET car_plugin_generate_messages_py)
  add_dependencies(car_plugin_generate_messages_py car_plugin_generate_messages_py)
endif()
