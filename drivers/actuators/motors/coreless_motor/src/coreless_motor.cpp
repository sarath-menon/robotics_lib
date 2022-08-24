#include "coreless_motor.hpp"

LOG_MODULE_DECLARE(cf_app);

CorelessMotor::CorelessMotor(const struct pwm_dt_spec &motor) : motor_{&motor} {

  // set motor id
  count++;
  id_ = count;

  rl::err status = this->initialize();

  if (status == 0) {
    LOG_INF("motor%d initialized", id_);
  } else {
    LOG_ERR("motor %d could not be initialized!", id_);
  }
}

rl::err CorelessMotor::initialize() {

  // check if the motor is ready
  if (!device_is_ready(motor_->dev)) {
    LOG_INF("PWM: motor is not ready");
    return -ENODEV;
  }

  // test the motor
  rl::err status = this->test();
  if (status != 0) {
    LOG_INF("PWM Error: failed to set pwm for motor %d", id_);
    return -1;
  }

  // return zero if initialization successful
  return 0;
}

rl::err CorelessMotor::test() {

  // set 10% speed for checking
  rl::err ret = this->set_speed(10);

  // wait for motors to tun
  k_sleep(K_MSEC(100));

  // turn of motors after testing
  ret = this->switch_off();

  return ret;
}

// switch of the motors
rl::err CorelessMotor::switch_off() {
  rl::err ret = this->set_speed(0.0f);
  return ret;
}

rl::err CorelessMotor::set_speed(std::uint32_t speed) {

  // clip speed if outside bounds
  // speed = std::min(speed, 1.0f);
  // speed = std::max(speed, 0.0f);

  std::uint32_t pulse_width = (speed * period) / 100;
  rl::err ret = pwm_set_dt(motor_, period, pulse_width);
  return ret;
}
