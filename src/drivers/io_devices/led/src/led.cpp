#include "led.hpp"

LOG_MODULE_DECLARE(cf_app);

Led::Led(const struct gpio_dt_spec &gpio) : gpio_{gpio} {

  rl::err ret{};

  // check if gpio is ready
  if (!device_is_ready(gpio_.port)) {
    printk("Error %d: LED device %s is not ready; ignoring it\n", ret,
           gpio_.port->name);
    // return -ENODEV;
  }

  // configure gpio pin as output
  ret = gpio_pin_configure_dt(&gpio_, GPIO_OUTPUT_ACTIVE);
  if (ret != 0) {
    printk("Error: failed to set led as output");
    // return -1;
  }

  // set led to off initially
  gpio_pin_set_dt(&gpio_, false);
}
