
create_interface_lib(drivers)

add_interface_sublib_ifdef(drivers actuators RL_ACTUATORS)
add_interface_sublib_ifdef(drivers io_devices RL_IO_DEVICES)
add_interface_sublib_ifdef(drivers sensors RL_SENSORS)


