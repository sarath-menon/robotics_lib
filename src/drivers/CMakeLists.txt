
create_interface_lib(NAME drivers
                    CONFIG RL_DRIVERS
                    LIBS 
                        actuators
                        interfaces
                        io_devices
                        logger
                        sensors
                    )