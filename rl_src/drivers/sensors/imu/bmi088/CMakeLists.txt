create_static_lib(NAME bmi088
                    CPP_FILES
                            src/bmi088.cpp
                            src/bmi088_acc.cpp
                            src/bmi088_gyro.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            math
                            imu_interface
                            i2c_dev
                            zephyr
                            zephyr_interface
                    )