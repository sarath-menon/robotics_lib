

template <typename Reg, typename Val>
rl::err I2CDev::set_parameter(const Reg param, const Val value) {

  std::uint8_t reg = static_cast<std::uint8_t>(param);
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