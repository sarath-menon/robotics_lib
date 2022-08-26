
create_static_lib(NAME led
                    CPP_FILES
                            src/led.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                            interfaces
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )