#include "led.hpp"

namespace rl::io_devices {

Led::Led(const struct gpio_dt_spec &gpio) : gpio_dev{gpio} {

  gpio_dev.check_ready();
  gpio_dev.set_mode(GPIOMode::output);
  gpio_dev.set_low();
}

rl::err Led::toggle() { return gpio_dev.toggle(); }

rl::err Led::set_high() { return gpio_dev.set_high(); }

rl::err Led::set_low() { return gpio_dev.set_low(); }

} // namespace rl::io_devices