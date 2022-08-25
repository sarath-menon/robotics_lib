
create_static_lib(NAME led
                    CONFIG 
                            RL_IO_DEVICES_LED
                    CPP_FILES
                            src/led.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )