
# set(CONFIG_NAME ENABLE_ROBOTICS_LIB)

create_interface_lib(NAME robotics_lib
                    CONFIG ENABLE_ROBOTICS_LIB
                    LIBS 
                        drivers
                        math
                        rl_common
                        communication
                        testing
                    )


