#pragma once

#include "bmi088_defs.hpp"
#include "i2c_dev.hpp"
#include "imu_dev.hpp"
#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

class BMI088_Gyro : public IMU {
public:
  //------ Constructor and Destructor-----------//

  BMI088_Gyro(const struct device *i2c_dev);

  // disable  copy constructor
  BMI088_Gyro() = delete;
  BMI088_Gyro(const BMI088_Gyro &) = delete;
  BMI088_Gyro &operator=(const BMI088_Gyro &) = delete;

  //------ Public Enums-----------//

  enum class Range : std::uint8_t {
    _2000dps = 0x00,
    _1000dps = 0x01,
    _500dps = 0x02,
    _250dps = 0x03,
    _125dps = 0x04
  };

  enum class Bandwidth : std::uint8_t {
    odr_2000hz_bw_532hz = 0x80,
    odr_2000hz_bw_230hz = 0x81,
    odr_1000hz_bw_116hz = 0x82,
    odr_400hz_bw_47hz = 0x83,
    odr_200hz_bw_23hz = 0x84,
    odr_100hz_bw_12hz = 0x85,
    odr_200hz_bw_64hz = 0x86,
    odr_100hz_bw_32hz = 0x87
  };

  enum class Reg : std::uint8_t {
    range = GYRO_RANGE,
    bandwidth = GYRO_BANDWIDTH,
    power_mode = GYRO_LPM1
  };

  //------ Public Functions-----------//
  // wakeup the imu from sleep mode (currently no diff btw power on and wakeup )
  rl::err wakeup() final;

  // put the imu in sleep mode (currently no diff btw power off and suspend )
  rl::err suspend() final;

  // initialize the device
  rl::err initialize() final;

  // read accelerometer data
  rl::err read() final;

private:
  //------  Private Variables--------//

  // mutiplying raw gyro readings by this factor converts it to deg/s unit
  float gyro_conv_factor_{};

  I2CDev i2c_dev;

  //------ Private Enums-----------//

  enum class PowerMode : std::uint8_t {
    active = 0x00,
    suspend = 0x80,
    deep_suspend = 0x20
  };

  //   //------ Private Functions-----------//

  rl::err set_gyro_conversion_factor();
};
