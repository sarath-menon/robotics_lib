#include "bmi088_acc.hpp"
#include "mathlib.hpp"
#include <math.h>
#include <zephyr/sys/byteorder.h>

LOG_MODULE_DECLARE(cf_app);

BMI088_Accel::BMI088_Accel(const struct device *i2c_dev)
    : I2CDev{i2c_dev, ACC_CHIP_ADDR} {
  rl::err status = this->initialize();
  if (status == 0) {
    LOG_INF("mpu6050 imu acc initialized");
  } else {
    LOG_ERR("mpu6050 imu acc could not be initialized!");
  }
}

rl::err BMI088_Accel::read() {

  std::uint8_t accel_data[6]{};

  // read 6 bytes: (acc_x_,acc_y, acc_z)
  std::int16_t err =
      i2c_burst_read(i2c_dev_, ACC_CHIP_ADDR, ACC_DATA_START, accel_data, 6);
  if (err < 0) {
    printk("imu: Failed to read data sample");
    return -EIO;
  }

  /* the imu sends data in big engian format (LSB first, MSB second). So,
   reverse order to little endian (MSB first, LSB second)*/
  std::int16_t accel_x = ((accel_data[1] << 8) | accel_data[0]);
  std::int16_t accel_y = ((accel_data[3] << 8) | accel_data[2]);
  std::int16_t accel_z = ((accel_data[5] << 8) | accel_data[4]);

  float accel_xf = accel_x * acc_conv_factor_;
  float accel_yf = accel_y * acc_conv_factor_;
  float accel_zf = accel_z * acc_conv_factor_;

  printk("accel: %.4f %.4f %.4f\n", accel_xf, accel_yf, accel_zf);

  return 0;
}

rl::err BMI088_Accel::initialize() {
  // check if i2c is ready
  if (!device_is_ready(i2c_dev_)) {
    LOG_ERR("I2C: mpu6050 imu acc is not ready");
    return -ENODEV;
  }

  // check device id
  if (i2c_reg_read_byte(i2c_dev_, ACC_CHIP_ADDR, ACC_CHIP_ID, &id_) < 0) {
    LOG_ERR("I2C: failed to read mpu6050 accel chip id");
    return -EIO;
  }

  if (id_ != ACC_WHO_AMI) {
    LOG_ERR("imu: invalid accel chip id");
    return -EINVAL;
  }

  this->set_parameter(Reg::conf, Conf::normal_400hz);
  this->set_parameter(Reg::range, Range::_3g);

  this->set_acc_conversion_factor();

  // suspend till after initialization to save power
  this->suspend();

  // return zero if initialization successful
  return 0;
}

rl::err BMI088_Accel::suspend() {
  rl::err err{};

  this->set_parameter(Reg::power, Power::off);
  status.sleep = false;

  k_sleep(K_MSEC(50));

  return err;
}

rl::err BMI088_Accel::wakeup() {
  rl::err err{};

  this->set_parameter(Reg::power, Power::on);
  status.sleep = true;

  k_sleep(K_MSEC(50));
  return err;
}

rl::err BMI088_Accel::set_acc_conversion_factor() {

  Range range;
  rl::err err = this->get_parameter(Reg::range, range);

  float g_range{};

  // update config struct
  switch (range) {
  case Range::_3g:
    g_range = 3.0f;
    break;
  case Range::_6g:
    g_range = 6.0f;
    break;
  case Range::_12g:
    g_range = 12.0f;
    break;
  case Range::_24g:
    g_range = 24.0f;
    break;
  default:
    break;
  }

  // calculate acc conversion factor
  acc_conv_factor_ = (rl::g * g_range) / 32768.0f;

  return err;
}