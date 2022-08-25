# Template for pure interface library
cmake_minimum_required(VERSION 3.20.0)
project(robotics_lib)

set(RL_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/top.cmake)

add_subdirectory(src)

