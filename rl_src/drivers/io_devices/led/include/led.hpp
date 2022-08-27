#pragma once

#include "gpio_dev.hpp"
#include "rl_common.hpp"
#include <cstdint>

namespace rl::io_devices {

class Led {
public:
  Led(const struct gpio_dt_spec &gpio);

  rl::err toggle();

  rl::err set_high();

  rl::err set_low();

private:
  GPIODev gpio_dev;
};

} // namespace rl::io_devices