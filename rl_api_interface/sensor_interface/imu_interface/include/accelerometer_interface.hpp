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

  // getter function
  inline auto chip_id() { return id_; }

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

  std::uint8_t id_{};

  //------ Structs-----------//

  struct Status {
    bool sleep;
    bool power_on;
  } status;

  //------ Functions-----------//
};
