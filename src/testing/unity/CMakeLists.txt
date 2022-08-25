create_static_lib(NAME unity
                    CONFIG 
                            ENABLE_ROBOTICS_LIB
                    CPP_FILES
                            src/unity.c
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            uart_dma
                            zephyr
                            zephyr_interface
                    )

