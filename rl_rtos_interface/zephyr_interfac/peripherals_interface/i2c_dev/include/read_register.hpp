
template <typename Reg, typename Val>
rl::err I2CDev::read_register(const Reg registr, Val &value) const {

  // check if Reg, Val is of type enum
  static_assert(std::is_enum_v<Reg> == true,
                "Parameter registr must be of type enum");
  static_assert(std::is_enum_v<Val> == true,
                "Parameter value  must be of type enum");

  auto reg = static_cast<rl::register_>(registr);
  std::uint8_t val;

  // read register value
  rl::err err = i2c_reg_read_byte(i2c_dev_, chip_addr_, reg, &val);

  value = static_cast<Val>(val);

  // error checking
  if (err < 0) {
    printk("imu: could not get parameter !\n");
    return -EIO;
  }

  return 0;
}
