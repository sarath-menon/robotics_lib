#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <cstdio>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

class I2CDev {
public:
  //------ Constructor and Destructor-----------//

  I2CDev(const struct device *i2c_dev, const std::uint8_t chip_addr)
      : i2c_dev_{i2c_dev}, chip_addr_{chip_addr} {};

  // disable default constructor and copy constructor
  I2CDev() = delete;
  I2CDev(const I2CDev &) = delete;
  I2CDev &operator=(const I2CDev &) = delete;

  //------ Functions-----------//

  // check if i2c device is ready
  rl::err check_ready();

  // read given number of bytes
  rl::err read_reg(const uint8_t start_addr, uint8_t *buf,
                   const uint32_t num_bytes);

  // read one byte
  rl::err read_reg(const uint8_t reg_addr, uint8_t *value);

  // write register value
  rl::err write_reg(const uint8_t reg_addr, const uint8_t value);

  // getter function
  inline auto chip_addr() { return chip_addr_; }

  // get a parameter in the imu register
  template <typename Reg, typename Val>
  rl::err get_parameter(const Reg param, Val &value);

  // set a parameter in the imu register
  template <typename Reg, typename Val>
  rl::err set_parameter(const Reg param, const Val value);

  //--------Private members---------------------------

protected:
  //------ Variables--------//

  const struct device *i2c_dev_{};

  const std::uint8_t chip_addr_{};

  //------ Functions-----------//
};

// template function defenitions
#include "get_param.hpp"
#include "set_param.hpp"