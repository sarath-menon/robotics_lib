#pragma once

#include "rl_common.hpp"
#include <cstdint>

class Gyro {
public:
  //------ Constructor and Destructor-----------//

  Gyro() = default;

  // disable and copy constructor
  Gyro(Gyro const &) = delete;
  Gyro &operator=(Gyro const &) = delete;

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

  // mutiplying raw gyro readings by this factor converts it to deg/s unit
  float gyro_conv_factor_{};

  //------ Structs-----------//

  // struct Status {
  //   bool sleep;
  //   bool power_on;
  // } status;
  enum Status : std::uint8_t { active, sleeping };
  Status status;

  //------ Functions-----------//
};
