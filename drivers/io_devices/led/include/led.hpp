#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

class Led {
public:
  Led(const struct gpio_dt_spec &gpio);

  inline auto toggle() { return gpio_pin_toggle_dt(&gpio_); }

  inline auto set_high() { return gpio_pin_set_dt(&gpio_, 1); }

  inline auto set_low() { return gpio_pin_set_dt(&gpio_, 0); }

  const auto &gpio() const { return gpio_; }

private:
  const struct gpio_dt_spec &gpio_{};
};