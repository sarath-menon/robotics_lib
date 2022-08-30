#pragma once

#include "rl_common.hpp"
#include <cstdint>

class Accelerometer {
public:
  //------ Constructor and Destructor-----------//

  Accelerometer() = default;

  // disable  copy constructor
  Accelerometer(const Accelerometer &) = delete;
  // disable  copy assignment operator
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

  // mutiplying raw accel readings by this factor converts it to m/s^2 units
  float acc_conv_factor_{};

  //------ Structs-----------//

  struct Status {
    bool sleep;
    bool power_on;
  } status;

  //------ Functions-----------//
};
