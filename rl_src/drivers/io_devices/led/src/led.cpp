#include "led.hpp"

LOG_MODULE_DECLARE(cf_app);

Led::Led(const struct gpio_dt_spec &gpio) : gpio_dev{gpio} {

  // rl::err ret{};

  // // check if gpio is ready
  // if (!device_is_ready(gpio_.port)) {
  //   printk("Error %d: LED device %s is not ready; ignoring it\n", ret,
  //          gpio_.port->name);
  //   // return -ENODEV;
  // }

  // // configure gpio pin as output
  // ret = gpio_pin_configure_dt(&gpio_, GPIO_OUTPUT_ACTIVE);
  // if (ret != 0) {
  //   printk("Error: failed to set led as output");
  //   // return -1;
  // }

  // // set led to off initially
  // gpio_pin_set_dt(&gpio_, false);

  gpio_dev.check_ready();
  gpio_dev.set_mode(GPIOMode::output);
  gpio_dev.set_low();
}

rl::err Led::toggle() { return gpio_dev.toggle(); }

rl::err Led::set_high() { return gpio_dev.set_high(); }

rl::err Led::set_low() { return gpio_dev.set_low(); }
