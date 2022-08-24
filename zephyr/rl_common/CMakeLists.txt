# Template for header only module

set(MODULE_NAME rl_common)

# list of libs to combine as one interface lib

set(INTERFACE_LIB_DEP
)

####### Do not modify !

add_library(${MODULE_NAME} INTERFACE)

target_include_directories(${MODULE_NAME} INTERFACE include)

target_link_libraries(${MODULE_NAME} INTERFACE ${INTERFACE_LIB_DEP})



