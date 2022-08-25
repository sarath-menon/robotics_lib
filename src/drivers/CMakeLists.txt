
create_interface_lib(NAME drivers
                    CONFIG RL_COMMUNICATION
                    LIBS 
                        actuators
                        interfaces
                        io_devices
                        logger
                        sensors
                    )