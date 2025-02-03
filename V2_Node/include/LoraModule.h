#ifndef LORAMODULE_H
#define LORAMODULE_H

#include <Arduino.h>
#include <EBYTE.h>
#include "EEPROMLib.h"
#include "Buzz.h"
#include "nodeId.h"

#define RXD2 PA3
#define TXD2 PA2

#define PIN_M0 PB0
#define PIN_M1 PB1
#define PIN_AUX -1

// Cấu trúc dữ liệu cảm biến
struct SensorData {
  char gatewayId[16]; // ID gateway dạng chuỗi
  int penCode;
  int nodeId;
  float t;  // Nhiệt độ
  float h;  // Độ ẩm
  float nh3; // NH3
  float h2s; // H2S
};

// Cấu trúc phản hồi ACK
struct AckData {
  char status[4];    // "OK" hoặc "ACK"
  char gatewayId[16];
  int penCode;
  int nodeId;
};

extern EBYTE Transceiver;
extern String gatewayId;
extern uint32_t waitDuration;


void LoraSetup();
void sendSensorData(String gatewayId, int penCode, int nodeId, float t, float h, float nh3, float h2s);
bool receiveLoraData(String &receivedData);
void processReceivedData(String &data);
void resetLoRaModule();
void beginSend();
void endSend();

#endif