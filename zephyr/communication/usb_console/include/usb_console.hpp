#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/zephyr.h>

class UsbConsole {
public:
  UsbConsole(const struct device *console);

private:
  const struct device *console_;

  std::uint32_t baudrate{};
  std::uint32_t dtr{};
};