# Template for pure interface library
cmake_minimum_required(VERSION 3.20.0)
project(robotics_lib)

set(RL_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/top.cmake)


create_interface_lib(robotics_lib)

add_interface_sublib(robotics_lib rl_src)
add_interface_sublib(drivers rl_api_interface)
add_interface_sublib(drivers rl_rtos_interface)


