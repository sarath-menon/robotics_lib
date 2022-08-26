#include "usb_console.hpp"

LOG_MODULE_DECLARE(cf_app);

UsbConsole::UsbConsole(const struct device *console) : console_{console} {

  // if (usb_enable(NULL)) {
  //   return;
  // }

  /* Poll if the DTR flag was set */
  // while (!dtr) {
  //   uart_line_ctrl_get(console_, UART_LINE_CTRL_DTR, &dtr);
  //   /* Give CPU resources to low priority threads. */
  //   k_sleep(K_MSEC(100));
  // }

  LOG_INF("Data terminal ready");

  rl::err ret{};

  // /* They are optional, we use them to test the interrupt endpoint */
  // ret = uart_line_ctrl_set(console_, UART_LINE_CTRL_DCD, 1);
  // if (ret) {
  //   LOG_WRN("Failed to set DCD, ret code %d", ret);
  // }

  // ret = uart_line_ctrl_set(console_, UART_LINE_CTRL_DSR, 1);
  // if (ret) {
  //   LOG_WRN("Failed to set DSR, ret code %d", ret);
  // }

  // /* Wait 1 sec for the host to do all settings */
  // k_busy_wait(1000000);

  // ret = uart_line_ctrl_get(console_, UART_LINE_CTRL_BAUD_RATE, &baudrate);
  // if (ret) {
  //   LOG_WRN("Failed to get baudrate, ret code %d", ret);
  // } else {
  //   LOG_INF("Baudrate detected: %d", baudrate);
  // }
}
