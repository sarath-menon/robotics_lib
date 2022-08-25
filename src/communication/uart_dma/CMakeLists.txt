create_static_lib(NAME uart_dma
                    CONFIG 
                            ENABLE_ROBOTICS_LIB
                    CPP_FILES
                            src/uart_dma.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )