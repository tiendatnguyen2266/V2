#ifndef LORAMODULE_H
#define LORAMODULE_H

#include "EBYTE.h"
#include <vector>
#include <mutex>
#include "buzzer.h"

#define PIN_M0 4
#define PIN_M1 22
#define PIN_AUX 21
#define RXD2 16
#define TXD2 17

struct LoraPacket {
  char command[20];
  char gatewayId[20];
  int penCode;
  int nodeId;
  char payload[50];
  uint8_t checksum;
};

extern EBYTE Transceiver;
extern std::vector<String> receivedDataList;
extern SemaphoreHandle_t xMutex;
extern bool LoraSender;

void Lora_Setup();
void Lora_receive(void *pvParameters);
void resetLoRaModule();
bool validatePacket(const LoraPacket& packet);

#endif