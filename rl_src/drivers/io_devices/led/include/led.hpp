#pragma once

#include "gpio_dev.hpp"
#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

class Led {
public:
  Led(const struct gpio_dt_spec &gpio);

  rl::err toggle();

  rl::err set_high();

  rl::err set_low();

private:
  GPIODev gpio_dev;
};