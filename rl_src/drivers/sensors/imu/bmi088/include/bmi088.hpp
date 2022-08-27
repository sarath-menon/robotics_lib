#pragma once

#include "bmi088_acc.hpp"
#include "bmi088_defs.hpp"
#include "bmi088_gyro.hpp"
#include "rl_common.hpp"
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

namespace rl::sensors::imu {

class BMI088 {
public:
  //------ Constructor and Destructor-----------//

  BMI088(const struct device *i2c_dev);

  // disable default constructor and copy constructor
  BMI088() = delete;
  BMI088(const BMI088 &) = delete;
  BMI088 &operator=(const BMI088 &) = delete;

  //------ Public variables--------//

  BMI088_Accel acc;
  BMI088_Gyro gyro;

private:
  //------ Private variables--------//

  const struct device *i2c_dev_{};
};

} // namespace rl::sensors::imu