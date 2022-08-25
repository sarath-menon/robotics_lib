
create_static_lib(NAME button
                    CONFIG 
                            RL_IO_DEVICES_BUTTON
                    CPP_FILES
                            src/button.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )


                    