#ifndef LORAMODULE_H
#define LORAMODULE_H

#include <Arduino.h>
#include <LoRa_E32.h>
#include "Buzz.h"
#include "EEPROMLib.h"
#include <nodeId.h>


// #define M0_PIN PA7
// #define M1_PIN PA6
// #define AUX_PIN PA5  // Chân tín hiệu nếu có dữ liệu truyền/nhận
// #define RX_PIN PA2
// #define TX_PIN PA3


extern String gatewayId;
extern int addrGatewayId;
extern uint32_t waitDuration;

void resetLoRaModule();
void LoraSetup(void);
void sendSensorData(String gatewayId, int penCode, int nodeId, float t, float h, float nh3, float h2s);
bool receiveLoraData(String &receivedData);
void processReceivedData(String &data);
void beginSend(void);
void endSend(void);

#endif