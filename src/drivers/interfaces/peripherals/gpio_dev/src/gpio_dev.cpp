#include "gpio_dev.hpp"

// set gpio pin to high state
rl::err GPIODev::set_high() { return gpio_pin_set_dt(&gpio_, 1); }

// set gpio pin to low state
rl::err GPIODev::set_low() { return gpio_pin_set_dt(&gpio_, 0); }

// toggle gpio pin state
rl::err GPIODev::toggle() { return gpio_pin_toggle_dt(&gpio_); }

// set gpio pin mode (input, output)
rl::err GPIODev::set_mode(const enum GPIOMode mode) {

  // configure gpio pin as output
  rl::err ret = gpio_pin_configure_dt(&gpio_, GPIO_OUTPUT_ACTIVE);
  if (ret != 0) {
    printk("Error: failed to set led as output");
    return -1;
  }

  return 0;
}

rl::err GPIODev::check_ready() { // check if gpio is ready

  rl::err ret = device_is_ready(gpio_.port);

  if (ret != 0) {
    printk("Error %d: LED device %s is not ready; ignoring it\n", ret,
           gpio_.port->name);
    return -1;
  }
  return 0;
}