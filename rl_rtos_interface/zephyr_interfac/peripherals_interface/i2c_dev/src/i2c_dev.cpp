#include "i2c_dev.hpp"

// check if i2c device is ready
rl::err I2CDev::check_bus_ready() {

  rl::err ret = device_is_ready(i2c_dev_);
  if (ret < 0) {
    printf("I2C: mpu6050 imu acc is not ready\n");
    return -ENODEV;
  }
  return 0;
}

// read register value
rl::err I2CDev::read_register(const rl::register_ reg_addr, uint8_t *buf,
                              const uint32_t num_bytes) const {
  return i2c_burst_read(i2c_dev_, chip_addr_, reg_addr, buf, num_bytes);
};

rl::err I2CDev::read_register(const rl::register_ reg_addr,
                              uint8_t *value) const {

  return i2c_reg_read_byte(i2c_dev_, chip_addr_, reg_addr, value);
}

rl::err I2CDev::write_register(const rl::register_ reg_addr,
                               const uint8_t value) const {
  return i2c_reg_write_byte(i2c_dev_, chip_addr_, reg_addr, value);
}
