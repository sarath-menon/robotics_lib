#pragma once

#include "bmi088_defs.hpp"
#include "i2c_dev.hpp"
#include "imu_interface.hpp"
#include "rl_common.hpp"
#include <cmath>
#include <cstdint>

class BMI088_Accel : public IMU {
public:
  //------ Constructor and Destructor-----------//

  BMI088_Accel(const struct device *i2c_dev);

  // disable default constructor and copy constructor
  BMI088_Accel() = delete;
  BMI088_Accel(const BMI088_Accel &) = delete;
  BMI088_Accel &operator=(const BMI088_Accel &) = delete;

  //------ Enums-----------//

  enum class Range : std::uint8_t {
    _3g = 0x00,
    _6g = 0x01,
    _12g = 0x02,
    _24g = 0x03
  };

  // hex values precomputed using a separte C++ program with std::bitset
  enum class Conf : std::uint8_t {
    normal_400hz = 0xAA,
    normal_800hz = 0xAB,
    normal_1600hz = 0xAC,
    osr2_400hz = 0x9A,
    osr2_800hz = 0x9B,
    osr2_1600hz = 0x9C,
    osr4_400hz = 0x8A,
    osr4_800hz = 0x8B,
    osr4_1600hz = 0x8C
  };

  enum class Reg : std::uint8_t {
    conf = ACC_CONF,
    range = ACC_RANGE,
    suspend = ACC_PWR_CONF,
    power = ACC_PWR_CTRL
  };

  //------ Functions-----------//
  // wakeup the imu from sleep mode (currently no diff btw power on and wakeup )
  rl::err wakeup() final;

  // put the imu in sleep mode (currently no diff btw power off and suspend )
  rl::err suspend() final;

  // initialize the device
  rl::err initialize() final;

  // read accelerometer data
  rl::err read() final;

  //--------Private members---------------------------

private:
  //------ Variables--------//

  // mutiplying raw accel readings by this factor converts it to m/s^2 units
  float acc_conv_factor_{};

  I2CDev i2c_dev;

  //------ Enums-----------//

  enum class Suspend : std::uint8_t { enable = 0x03, disable = 0x00 };

  enum class Power : std::uint8_t { on = 0x04, off = 0x00 };

  //------ Functions-----------//

  rl::err set_acc_conversion_factor();
};
