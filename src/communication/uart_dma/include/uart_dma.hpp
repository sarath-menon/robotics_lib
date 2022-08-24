#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/zephyr.h>

class UartDma {
public:
  UartDma(const struct device *uart_dev);

  std::int16_t enable_dma_receiving();

  std::int16_t send_dma(const std::uint8_t *buf, size_t len);

  void print_rxbuf();

private:
  const struct device *uart_dev;

  int err;
  inline constexpr static std::uint8_t rx_buf_size = 20;
  std::uint8_t rx_buf[rx_buf_size]{};
};