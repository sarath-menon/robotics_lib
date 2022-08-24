# Template for pure interface library
cmake_minimum_required(VERSION 3.20.0)
project(robotics_lib)



set(LIB_NAME robotics_lib)

# list of libs to combine as one interface lib
set(SUB_LIBS 
drivers
math
rl_common
communication
testing
)

####### Do not modify !

if(CONFIG_ENABLE_ROBOTICS_LIB)
message(".......Robotics lib enabled.......")

add_library(${LIB_NAME} INTERFACE)

target_link_libraries(${LIB_NAME} INTERFACE ${SUB_LIBS})

foreach(LIB ${SUB_LIBS})
    add_subdirectory(src/${LIB})
endforeach()

endif()

