#pragma once

#include "rl_common.hpp"
#include <cstdint>

class Accelerometer {
public:
  //------ Constructor and Destructor-----------//

  // Accelerometer(const std::uint8_t chip_addr) : chip_addr_{chip_addr} {};
  Accelerometer() = default;

  // disable  copy constructor
  // virtual ~Accelerometer() = default;
  Accelerometer(const Accelerometer &) = delete;
  Accelerometer &operator=(const Accelerometer &) = delete;

  //------  Public Functions-----------//

protected:
  //------  Protected Functions-----------//

  // wakeup the imu from sleep mode (currently no diff btw power on and wakeup )
  virtual rl::err wakeup() { return 0; };

  // put the imu in sleep mode (currently no diff btw power off and suspend )
  virtual rl::err suspend() { return 0; };

  // initialize the device
  virtual rl::err initialize() { return 0; };

  // read accelerometer data
  virtual rl::err read() { return 0; };

  //--------Private members---------------------------

  //------ Variables--------//

  //------ Structs-----------//

  struct Status {
    bool sleep;
    bool power_on;
  } status;

  //------ Functions-----------//
};
