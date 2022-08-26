create_static_lib(NAME imu_dev
                    CPP_FILES
                            src/imu_dev.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            math
                            zephyr
                            zephyr_interface
                    )