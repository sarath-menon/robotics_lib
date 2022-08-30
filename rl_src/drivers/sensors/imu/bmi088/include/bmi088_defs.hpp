#pragma once
#include "rl_common.hpp"
#include <cstdint>

// Accelerometer
rl::register_ constexpr static ACC_CHIP_ADDR = 0x18;
rl::register_ constexpr static ACC_CHIP_ID = 0x00;
rl::register_ constexpr static ACC_WHO_AMI = 0x1E;

rl::register_ constexpr static ACC_PWR_CTRL = 0x7D;
rl::register_ constexpr static ACC_DATA_START = 0x12;
rl::register_ constexpr static ACC_CONF = 0x40;
rl::register_ constexpr static ACC_RANGE = 0x41;
rl::register_ constexpr static ACC_PWR_CONF = 0x7C;

// Gyroscope

rl::register_ constexpr static GYRO_CHIP_ADDR = 0x69;
rl::register_ constexpr static GYRO_CHIP_ID = 0x00;
rl::register_ constexpr static GYRO_WHO_AMI = 0x0F;

rl::register_ constexpr static GYRO_DATA_START = 0x02;
rl::register_ constexpr static GYRO_LPM1 = 0x11;
rl::register_ constexpr static GYRO_RANGE = 0x0F;
rl::register_ constexpr static GYRO_BANDWIDTH = 0x10;

// rl::register_ constexpr static GYRO_SOFTRESET = 0x14;