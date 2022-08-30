#include "bmi088.hpp"
LOG_MODULE_DECLARE(cf_app);

namespace rl::sensors::imu {

BMI088::BMI088(struct device const *const i2c_dev)
    : acc(i2c_dev), gyro(i2c_dev), i2c_dev_{i2c_dev} {}

} // namespace rl::sensors::imu