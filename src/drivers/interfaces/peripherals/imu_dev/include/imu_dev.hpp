#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

class IMU {
public:
  //------ Constructor and Destructor-----------//

  IMU(const struct device *i2c_dev, const std::uint8_t chip_addr)
      : i2c_dev_{i2c_dev}, chip_addr_{chip_addr} {};

  // disable default constructor and copy constructor
  IMU() = delete;
  IMU(const IMU &) = delete;
  IMU &operator=(const IMU &) = delete;

  //------ Functions-----------//

  // get a parameter in the imu register
  template <typename Reg, typename Val>
  rl::err get_parameter(const Reg param, Val &value);

  // set a parameter in the imu register
  template <typename Reg, typename Val>
  rl::err set_parameter(const Reg param, const Val value);

  // wakeup the imu from sleep mode (currently no diff btw power on and wakeup )
  virtual rl::err wakeup() { return 0; };

  // put the imu in sleep mode (currently no diff btw power off and suspend )
  virtual rl::err suspend() { return 0; };

  // initialize the device
  virtual rl::err initialize() { return 0; };

  // read accelerometer data
  virtual rl::err read() { return 0; };

  // getter function
  inline auto chip_id() { return id_; }

  //--------Private members---------------------------

protected:
  //------ Variables--------//

  const struct device *i2c_dev_{};

  const std::uint8_t chip_addr_{};

  std::uint8_t id_{};

  //------ Structs-----------//

  struct Status {
    bool sleep;
    bool power_on;
  } status;

  //------ Functions-----------//
};

// template function defenitions
#include "get_param.hpp"
#include "set_param.hpp"