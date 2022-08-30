#pragma once

#include "rl_common.hpp"
#include <cstdint>

class IMU {
public:
  //------ Constructor and Destructor-----------//

  IMU(rl::register_ const chip_addr) : chip_addr_{chip_addr} {};

  // disable default constructor and copy constructor
  IMU() = delete;
  // virtual ~IMU() = default;
  IMU(IMU const &) = delete;
  IMU &operator=(IMU const &) = delete;

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

  rl::register_ const chip_addr_{};

  std::uint8_t id_{};

  //------ Structs-----------//

  struct Status {
    bool sleep;
    bool power_on;
  } status;

  //------ Functions-----------//
};
