#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
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
  rl::err check_bus_ready();

  // read given number of bytes
  rl::err read_reg(const uint8_t start_addr, uint8_t *buf,
                   const uint32_t num_bytes);

  // read one byte
  rl::err read_reg(const uint8_t reg_addr, uint8_t *value);

  // write register value
  rl::err write_reg(const uint8_t reg_addr, const uint8_t value) const;

  // getter function
  inline auto chip_addr() const { return chip_addr_; }

  // get a parameter in the imu register
  template <typename Reg, typename Val>
  rl::err read_register(const Reg param, Val &value);

  // set a parameter in the imu register
  template <typename Reg, typename Val>
  rl::err write_register(const Reg param, const Val value) const;

  //--------Private members---------------------------

protected:
  //------ Variables--------//

  const struct device *i2c_dev_{};

  const std::uint8_t chip_addr_{};

  //------ Functions-----------//
};

// template function defenitions
#include "read_register.hpp"
#include "write_register.hpp"