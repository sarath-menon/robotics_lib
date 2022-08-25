create_static_lib(NAME i2c_dev
                    CONFIG 
                            ENABLE_ROBOTICS_LIB
                    CPP_FILES
                            src/i2c_dev.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            math
                            zephyr
                            zephyr_interface
                    )