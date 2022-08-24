#pragma once

#include "uart_dma.hpp"
#include <cstdint>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/zephyr.h>

// #define SYSLINK_MTU 64

inline constexpr static std::uint8_t SYSLINK_MTU = 64;

#pragma pack(1)
struct SyslinkPacket {
  std::uint8_t type;
  std::uint8_t length;
  std::uint8_t data[SYSLINK_MTU];
  std::uint8_t cksum[2];
};

#pragma pack(1)
enum class SyslinkState {
  waitForFirstStart,
  waitForSecondStart,
  waitForType,
  waitForLength,
  waitForData,
  waitForChksum1,
  waitForChksum2
};

class Syslink {
public:
  Syslink() = delete;
  Syslink(UartDma *uart_dma);

  void initiate();

  int syslinkSendPacket(SyslinkPacket *slp);

  void systemRequestShutdown();

  void systemRequestNRFVersion();

private:
  SyslinkState syslink_rxstate;

  SyslinkPacket syslink_msg{};

  UartDma *uart_dma;

  // data + startbytes(2) + type(1) + length(2) + checksum(2)
  uint8_t sendBuffer[SYSLINK_MTU + 6]{};

private:
  constexpr static std::uint8_t CRTP_START_BYTE = 0xAA;
  constexpr static std::uint8_t SYSLINK_START_BYTE1 = 0xBC;
  constexpr static std::uint8_t SYSLINK_START_BYTE2 = 0xCF;

  // Defined packet types
  constexpr static std::uint8_t SYSLINK_GROUP_MASK = 0xF0;

  constexpr static std::uint8_t SYSLINK_RADIO_GROUP = 0x00;
  constexpr static std::uint8_t SYSLINK_RADIO_RAW = 0x00;
  constexpr static std::uint8_t SYSLINK_RADIO_CHANNEL = 0x01;
  constexpr static std::uint8_t SYSLINK_RADIO_DATARATE = 0x02;
  constexpr static std::uint8_t SYSLINK_RADIO_CONTWAVE = 0x03;
  constexpr static std::uint8_t SYSLINK_RADIO_RSSI = 0x04;
  constexpr static std::uint8_t SYSLINK_RADIO_ADDRESS = 0x05;
  constexpr static std::uint8_t SYSLINK_RADIO_RAW_BROADCAST = 0x06;
  constexpr static std::uint8_t SYSLINK_RADIO_POWER = 0x07;
  constexpr static std::uint8_t SYSLINK_RADIO_P2P = 0x08;
  constexpr static std::uint8_t SYSLINK_RADIO_P2P_ACK = 0x09;
  constexpr static std::uint8_t SYSLINK_RADIO_P2P_BROADCAST = 0x0A;

  constexpr static std::uint8_t SYSLINK_PM_GROUP = 0x10;
  constexpr static std::uint8_t SYSLINK_PM_SOURCE = 0x10;
  constexpr static std::uint8_t SYSLINK_PM_ONOFF_SWITCHOFF = 0x11;
  constexpr static std::uint8_t SYSLINK_PM_BATTERY_VOLTAGE = 0x12;
  constexpr static std::uint8_t SYSLINK_PM_BATTERY_STATE = 0x13;
  constexpr static std::uint8_t SYSLINK_PM_BATTERY_AUTOUPDATE = 0x14;
  constexpr static std::uint8_t SYSLINK_PM_SHUTDOWN_REQUEST = 0x15;
  constexpr static std::uint8_t SYSLINK_PM_SHUTDOWN_ACK = 0x16;
  constexpr static std::uint8_t SYSLINK_PM_LED_ON = 0x17;
  constexpr static std::uint8_t SYSLINK_PM_LED_OFF = 0x18;

  constexpr static std::uint8_t SYSLINK_OW_GROUP = 0x20;
  constexpr static std::uint8_t SYSLINK_OW_SCAN = 0x20;
  constexpr static std::uint8_t SYSLINK_OW_GETINFO = 0x21;
  constexpr static std::uint8_t SYSLINK_OW_READ = 0x22;
  constexpr static std::uint8_t SYSLINK_OW_WRITE = 0x23;

  constexpr static std::uint8_t SYSLINK_SYS_GROUP = 0x30;
  constexpr static std::uint8_t SYSLINK_SYS_NRF_VERSION = 0x30;

  constexpr static std::uint8_t SYSLINK_DEBUG_GROUP = 0xF0;
  constexpr static std::uint8_t SYSLINK_DEBUG_PROBE = 0xF0;
};