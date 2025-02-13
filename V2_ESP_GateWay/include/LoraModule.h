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
  char command[10];
  char gatewayId[20];
  int penCode;
  int nodeId;
  char payload[100];
  uint16_t checksum; // Thêm trường lưu checksum

  void calculateChecksum() {
      uint16_t sum = 0;
      // Cộng tất cả các byte của các trường (tùy theo yêu cầu của bạn)
      for (size_t i = 0; i < sizeof(command); i++) {
          sum += command[i];
      }
      for (size_t i = 0; i < sizeof(gatewayId); i++) {
          sum += gatewayId[i];
      }
      for (size_t i = 0; i < sizeof(payload); i++) {
          sum += payload[i];
      }
      sum += penCode;
      sum += nodeId;
      checksum = sum;
  }
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