#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

namespace rl::actuators::motors {

class CorelessMotor {
public:
  CorelessMotor(const struct pwm_dt_spec &motor);

public:
  // test the motor
  rl::err test();

  /* set speed as a value between 0 and 1
    0.0 = zero speed
    1.0 = max speed */
  rl::err set_speed(std::uint32_t speed);

  // switch of the motors
  rl::err switch_off();

  // getter functions
  const auto &id() const { return id_; }

private:
  rl::err initialize();

private:
  const struct pwm_dt_spec *motor_;

  // keeps track of the number of motors
  inline static std::uint8_t count{};

  // unique motor id
  std::uint8_t id_{};

  // period of pwm signal in milliseconds
  const std::uint32_t period = 3000;
};

} // namespace rl::actuators::motors