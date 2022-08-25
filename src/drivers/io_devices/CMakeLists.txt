

create_interface_lib(io_devices)

add_interface_sublib_ifdef(io_devices button RL_IO_DEVICES_BUTTON)
add_interface_sublib_ifdef(io_devices led RL_IO_DEVICES_LED)
                    