

template <typename Reg, typename Val>
rl::err I2CDev::write_register(const Reg registr, const Val value) {

  // error checking
  static_assert(std::is_enum_v<Reg> == true,
                "Parameter registr must be of type enum");
  static_assert(std::is_enum_v<Val> == true,
                "Parameter value  must be of type enum");

  std::uint8_t reg = static_cast<std::uint8_t>(registr);
  std::uint8_t val = static_cast<std::uint8_t>(value);

  // write register value
  rl::err err = i2c_reg_write_byte(i2c_dev_, chip_addr_, reg, val);

  // error checking
  if (err < 0) {
    printk("imu: could not set parameter !\n");
    return -EIO;
  }

  // wait for imu to settle
  k_sleep(K_MSEC(10));

  return 0;
}