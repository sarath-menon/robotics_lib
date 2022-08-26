
create_static_lib(NAME coreless_motor
                    CPP_FILES
                            src/coreless_motor.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )