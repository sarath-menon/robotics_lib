#include "syslink.hpp"
#include "string.h"

Syslink::Syslink(UartDma *uart_dma) : uart_dma{uart_dma} {}

int Syslink::syslinkSendPacket(SyslinkPacket *slp) {
  int i = 0;
  int dataSize;
  uint8_t cksum[2] = {0};

  //   ASSERT(slp->length <= SYSLINK_MTU);

  // set start bytes, msg type, msg length
  sendBuffer[0] = SYSLINK_START_BYTE1;
  sendBuffer[1] = SYSLINK_START_BYTE2;
  sendBuffer[2] = slp->type;
  sendBuffer[3] = slp->length;

  // set data packets
  memcpy(&sendBuffer[4], slp->data, slp->length);

  dataSize = slp->length + 6;

  // Calculate checksum delux
  for (i = 2; i < dataSize - 2; i++) {
    cksum[0] += sendBuffer[i];
    cksum[1] += cksum[0];
  }

  // set checksum
  sendBuffer[dataSize - 2] = cksum[0];
  sendBuffer[dataSize - 1] = cksum[1];

  // uartslkSendDataDmaBlocking(dataSize, sendBuffer);
  uart_dma->send_dma(sendBuffer, SYSLINK_MTU + 6);

  return 0;
}

void Syslink::systemRequestNRFVersion() {
  SyslinkPacket slp;

  slp.type = SYSLINK_SYS_NRF_VERSION;
  slp.length = 0;
  this->syslinkSendPacket(&slp);
}

void Syslink::systemRequestShutdown() {
  SyslinkPacket slp;

  slp.type = SYSLINK_PM_ONOFF_SWITCHOFF;
  slp.length = 0;
  this->syslinkSendPacket(&slp);
}