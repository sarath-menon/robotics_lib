#include "bmi088.hpp"
LOG_MODULE_DECLARE(cf_app);

BMI088::BMI088(const struct device *i2c_dev)
    : acc(i2c_dev), gyro(i2c_dev), i2c_dev_{i2c_dev} {}
