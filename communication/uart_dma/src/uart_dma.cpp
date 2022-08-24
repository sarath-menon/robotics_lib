#include "uart_dma.hpp"

static void uart_cb(const struct device *dev, struct uart_event *evt,
                    void *user_data);

UartDma::UartDma(const struct device *uart_dev) : uart_dev{uart_dev} {

  if (!device_is_ready(uart_dev)) {
    printk("UART device not found!");
    // LOG_ERR("UART device not found!");
    // return -1;
  }

  // set async callback
  rl::err flag = uart_callback_set(uart_dev, uart_cb, NULL);
  if (flag) {
    printk("Err:%d Could not set uart callback!\n", err);
    // return err;
  }
}

std::int16_t UartDma::enable_dma_receiving() {
  // enable uart receiving
  std::int16_t err = uart_rx_enable(uart_dev, rx_buf, rx_buf_size, 100);
  if (err) {
    printk("Error %d: Could not enable uart async receive !\n", err);
    return err;
  }
  return 0;
}

std::int16_t UartDma::send_dma(const std::uint8_t *buf, size_t len) {

  err = uart_tx(uart_dev, buf, len, SYS_FOREVER_US);
  if (err) {
    printk("Error %d: Could not send uart async msg\n", err);
  }
  return 0;
}

static void uart_cb(const struct device *dev, struct uart_event *evt,
                    void *user_data) {
  // rl::err flag;

  switch (evt->type) {

  // Whole TX buffer was transmitted.
  case UART_TX_DONE:
    // printk("tx done\n");
    break;

    // Transmitting aborted due to timeout or uart_tx_abort call.
  case UART_TX_ABORTED:
    printk("tx aborted\n");
    break;

    // Received data is ready for processing (also generated in some other
    // cases (eg.when buffer is full, When RX timeout occurred etc )  See docs
  case UART_RX_RDY:
    printk("recv\n");
    // err = uart_tx(dev, ack_buf, rx_buf_size, SYS_FOREVER_US);
    // if (err) {
    //   printk("Error %d: Could not send uart async msg\n", err);
    // }
    break;

  /* receiving has started for a new buffer. r, i.e. it’s time to provide a next
   buffer for a seamless switchover to it. For continuous reliable receiving,
   user should provide another RX buffer in response to this event, using
   uart_rx_buf_rsp function*/
  case UART_RX_BUF_REQUEST:
    printk("rx buf req\n");
    break;

  // Buffer is no longer used by UART driver.
  case UART_RX_BUF_RELEASED:
    printk("rx buf released\n");
    break;

  // RX has been disabled, can be reenabled
  case UART_RX_DISABLED:
    printk("rx disabled");
    break;

  // RX has stopped due to external event.
  case UART_RX_STOPPED:
    printk("rx stopped");
    break;
  }
}

void UartDma::print_rxbuf() {
  static int count = -1;
  printk("buf:%d\n", rx_buf[count + 1]);
  count++;
}