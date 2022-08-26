#include "bmi088_gyro.hpp"
#include "mathlib.hpp"
#include <math.h>
#include <zephyr/sys/byteorder.h>

LOG_MODULE_DECLARE(cf_app);

BMI088_Gyro::BMI088_Gyro(const struct device *i2c_dev)
    : IMU{i2c_dev, ACC_CHIP_ADDR}, i2c_dev{i2c_dev, ACC_CHIP_ADDR} {
  rl::err status = this->initialize();
  if (status == 0) {
    LOG_INF("mpu6050 imu gyro initialized");
  } else {
    LOG_ERR("mpu6050 imu gyro could not be initialized!");
  }
}

rl::err BMI088_Gyro::read() {

  std::uint8_t gyro_data[6]{};

  // read 6 bytes: (gyro_x_,gyro_y, gyro_z)
  std::int16_t err = i2c_dev.read_reg(GYRO_DATA_START, gyro_data, 6);
  if (err < 0) {
    printk("imu: Failed to read data sample");
    return -EIO;
  }

  /* the imu sends data in big engian format (LSB first, MSB second). So,
   reverse order to little endian (MSB first, LSB second)*/
  std::int16_t gyro_x = ((gyro_data[1] << 8) | gyro_data[0]);
  std::int16_t gyro_y = ((gyro_data[3] << 8) | gyro_data[2]);
  std::int16_t gyro_z = ((gyro_data[5] << 8) | gyro_data[4]);

  float gyro_xf = gyro_x * gyro_conv_factor_;
  float gyro_yf = gyro_y * gyro_conv_factor_;
  float gyro_zf = gyro_z * gyro_conv_factor_;

  printk("gyro: %.4f %.4f %.4f\n", gyro_xf, gyro_yf, gyro_zf);

  return 0;
}

rl::err BMI088_Gyro::initialize() {
  // check if i2c is ready
  if (!device_is_ready(i2c_dev_)) {
    LOG_ERR("I2C: mpu6050 imu gyro is not ready");
    return -ENODEV;
  }

  // check device id
  if (i2c_dev.read_reg(GYRO_CHIP_ID, &id_) < 0) {
    LOG_ERR("I2C: failed to read mpu6050 gyro chip id");
    return -EIO;
  }

  if (id_ != GYRO_WHO_AMI) {
    LOG_ERR("imu: invalid gyro chip id");
    return -EINVAL;
  }

  this->set_parameter(Reg::bandwidth, Bandwidth::odr_2000hz_bw_532hz);
  this->set_parameter(Reg::range, Range::_2000dps);

  this->set_gyro_conversion_factor();

  // suspend  after initialization to save power
  this->suspend();

  // return zero if initialization successful
  return 0;
}

rl::err BMI088_Gyro::suspend() {
  rl::err err{};

  this->set_parameter(Reg::power_mode, PowerMode::suspend);
  status.sleep = true;

  k_sleep(K_MSEC(50));

  return err;
}

rl::err BMI088_Gyro::wakeup() {
  rl::err err{};

  this->set_parameter(Reg::power_mode, PowerMode::active);
  status.sleep = false;

  k_sleep(K_MSEC(50));

  return err;
}

rl::err BMI088_Gyro::set_gyro_conversion_factor() {

  Range range;
  rl::err err = this->get_parameter(Reg::range, range);

  float dps{};

  // update config struct
  switch (range) {
  case Range::_2000dps:
    dps = 2000.0f;
    break;
  case Range::_1000dps:
    dps = 1000.0f;
    break;
  case Range::_500dps:
    dps = 500.0f;
    break;
  case Range::_250dps:
    dps = 250.0f;
    break;
  case Range::_125dps:
    dps = 125.0f;
    break;
  default:
    break;
  }

  // calculate acc conversion factor
  gyro_conv_factor_ = dps / 32768.0f;

  return err;
}