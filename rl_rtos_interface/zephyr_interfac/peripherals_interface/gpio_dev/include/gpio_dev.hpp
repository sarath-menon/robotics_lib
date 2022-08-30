#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

enum class GPIOMode { input = GPIO_INPUT, output = GPIO_OUTPUT_INACTIVE };

class GPIODev {
public:
  //------ Constructor and Destructor-----------//

  constexpr GPIODev(const struct gpio_dt_spec &gpio) : gpio_{gpio} {};

  // disable default constructor and copy constructor
  GPIODev() = delete;
  GPIODev(const GPIODev &) = delete;
  GPIODev &operator=(const GPIODev &) = delete;

  //------ Functions-----------//

  // set gpio pin is ready
  rl::err check_ready();

  // set gpio pin to high state
  rl::err set_high();

  // set gpio pin to low state
  rl::err set_low();

  // toggle gpio pin state
  rl::err toggle();

  // set gpio pin mode (input, output)
  rl::err set_mode(enum GPIOMode const mode);

  // getter function
  auto consteval &gpio() const { return gpio_; }

  //--------Protected members---------------------------

protected:
  //------ Variables--------//

  struct gpio_dt_spec const &gpio_{};

  //------ Structs-----------//

  //------ Functions-----------//
};
