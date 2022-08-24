set(MODULE_NAME logger)


set(INTERFACE_LIB_DEP
zephyr
zephyr_interface
)

####### Do not modify !

add_library(${MODULE_NAME} INTERFACE)

target_include_directories(${MODULE_NAME} INTERFACE include)

target_link_libraries(${MODULE_NAME} INTERFACE ${INTERFACE_LIB_DEP})


