#pragma once
#include <cstdint>

// Accelerometer
constexpr static std::uint8_t ACC_CHIP_ADDR = 0x18;
constexpr static std::uint8_t ACC_CHIP_ID = 0x00;
constexpr static std::uint8_t ACC_WHO_AMI = 0x1E;

constexpr static std::uint8_t ACC_PWR_CTRL = 0x7D;
constexpr static std::uint8_t ACC_DATA_START = 0x12;
constexpr static std::uint8_t ACC_CONF = 0x40;
constexpr static std::uint8_t ACC_RANGE = 0x41;
constexpr static std::uint8_t ACC_PWR_CONF = 0x7C;

// Gyroscope

constexpr static std::uint8_t GYRO_CHIP_ADDR = 0x69;
constexpr static std::uint8_t GYRO_CHIP_ID = 0x00;
constexpr static std::uint8_t GYRO_WHO_AMI = 0x0F;

constexpr static std::uint8_t GYRO_DATA_START = 0x02;
constexpr static std::uint8_t GYRO_LPM1 = 0x11;
constexpr static std::uint8_t GYRO_RANGE = 0x0F;
constexpr static std::uint8_t GYRO_BANDWIDTH = 0x10;

// constexpr static std::uint8_t GYRO_SOFTRESET = 0x14;