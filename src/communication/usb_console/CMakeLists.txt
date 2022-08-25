
create_static_lib(NAME usb_console
                    CONFIG 
                            ENABLE_ROBOTICS_LIB
                    CPP_FILES
                            src/usb_console.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )

