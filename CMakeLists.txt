# Template for pure interface library
cmake_minimum_required(VERSION 3.20.0)
project(robotics_lib)

include(functions.cmake)

add_subdirectory(src)

# add_module(NAME imu LIBS lib1 lib2)
