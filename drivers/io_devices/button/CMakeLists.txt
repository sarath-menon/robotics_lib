set(MODULE_NAME button)


# list of c++ source files
set(CPP_FILES
src/${MODULE_NAME}.cpp
)

# list of library dependendcies
set(PUBLIC_LIB_DEP
rl_common
)

set(PRIVATE_LIB_DEP
zephyr
zephyr_interface
)

####### Do not modify !

add_library(${MODULE_NAME} STATIC ${CPP_FILES})

target_include_directories(${MODULE_NAME} PUBLIC include)

target_link_libraries(${MODULE_NAME} PUBLIC ${PUBLIC_LIB_DEP})

target_link_libraries(${MODULE_NAME} PRIVATE ${PRIVATE_LIB_DEP})

