
# set(CONFIG_NAME ENABLE_ROBOTICS_LIB)

# create_interface_lib(NAME robotics_lib
#                     CONFIG ENABLE_ROBOTICS_LIB
#                     LIBS 
#                         drivers
#                         math
#                         rl_common
#                         communication
#                         testing
#                     )


create_interface_lib(robotics_lib)

add_interface_sublib_ifdef(robotics_lib drivers RL_DRIVERS)
add_interface_sublib_ifdef(robotics_lib communication RL_COMMUNICATION)
add_interface_sublib_ifdef(robotics_lib testing RL_TESTING)

add_interface_sublib(robotics_lib math)
add_interface_sublib(robotics_lib rl_common)