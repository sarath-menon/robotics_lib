create_static_lib(NAME imu_interface
                    CPP_FILES
                            src/imu_interface.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
   

                    )