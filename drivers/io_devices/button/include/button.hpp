#pragma once

#include "rl_common.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

class Button {
public:
  Button(const struct gpio_dt_spec &gpio) : gpio{gpio} {

    // check whether gpio pin is ready
    if (!device_is_ready(gpio.port)) {
      printk("Error: gpio device %s is not ready\n", gpio.port->name);
      //   return -ENODEV;
    }

    // configure gpio pin as input
    rl::err ret = gpio_pin_configure_dt(&gpio, GPIO_INPUT);
    if (ret != 0) {
      printk("Error %d: failed to configure %s pin %d\n", ret, gpio.port->name,
             gpio.pin);
      //   return -1;
    }

    // configure interrupt on gpio
    ret = gpio_pin_interrupt_configure_dt(&gpio, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
      printk("Error %d: failed to configure interrupt on %s pin %d\n", ret,
             gpio.port->name, gpio.pin);
      //   return -1;
    }
  }

  void set_callback(gpio_callback_handler_t handler) {
    gpio_init_callback(&button_cb_data, handler, BIT(gpio.pin));
    gpio_add_callback(gpio.port, &button_cb_data);
  }

  const struct gpio_dt_spec &gpio{};

private:
  // gpio callback
  struct gpio_callback button_cb_data;
};