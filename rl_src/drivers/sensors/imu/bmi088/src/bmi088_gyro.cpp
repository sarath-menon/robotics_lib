#include "bmi088_gyro.hpp"

// LOG_MODULE_DECLARE(cf_app);

BMI088_Gyro::BMI088_Gyro(const struct device *i2c_dev)
    : IMU{GYRO_CHIP_ADDR}, i2c_dev{i2c_dev, GYRO_CHIP_ADDR} {
  rl::err status = this->initialize();
  if (status == 0) {
    printf("mpu6050 imu gyro initialized\n");
  } else {
    printf("mpu6050 imu gyro could not be initialized!\n");
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

  i2c_dev.check_ready();

  // check device id
  if (i2c_dev.read_reg(GYRO_CHIP_ID, &id_) < 0) {
    printf("I2C: failed to read mpu6050 gyro chip id\n");
    return -EIO;
  }

  if (id_ != GYRO_WHO_AMI) {
    printf("imu: invalid gyro chip id\n");
    return -EINVAL;
  }

  i2c_dev.set_parameter(Reg::bandwidth, Bandwidth::odr_2000hz_bw_532hz);
  i2c_dev.set_parameter(Reg::range, Range::_2000dps);

  this->set_gyro_conversion_factor();

  // suspend  after initialization to save power
  this->suspend();

  // return zero if initialization successful
  return 0;
}

rl::err BMI088_Gyro::suspend() {
  rl::err err{};

  i2c_dev.set_parameter(Reg::power_mode, PowerMode::suspend);
  status.sleep = true;

  k_sleep(K_MSEC(50));

  return err;
}

rl::err BMI088_Gyro::wakeup() {
  rl::err err{};

  i2c_dev.set_parameter(Reg::power_mode, PowerMode::active);
  status.sleep = false;

  k_sleep(K_MSEC(50));

  return err;
}

rl::err BMI088_Gyro::set_gyro_conversion_factor() {

  Range range;
  rl::err err = i2c_dev.get_parameter(Reg::range, range);

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