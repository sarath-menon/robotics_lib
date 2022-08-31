#pragma once

#include "rl_common.hpp"
#include <cstdint>

enum class BusType : std::uint8_t { i2c, spi };

class Accelerometer {
public:
  //------ Constructor and Destructor-----------//

  Accelerometer() = default;
  Accelerometer(enum BusType bus_type) : bus_type{bus_type} {}

  // disable  copy constructor
  Accelerometer(Accelerometer const &) = delete;
  // disable  copy assignment operator
  Accelerometer &operator=(Accelerometer const &) = delete;

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

  //-------- Private Enums ---------------------------

  enum Status : std::uint8_t { active, sleeping };

  //-------- Protected  Variables ---------------------------

  // mutiplying raw accel readings by this factor converts it to m/s^2 units
  float acc_conv_factor_{};

  BusType bus_type{};
  Status status{};

  //------ Functions-----------//
};
