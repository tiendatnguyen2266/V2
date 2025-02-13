#include "LoraModule.h"

EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AUX);
std::vector<String> receivedDataList;
SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();
bool LoraSender = false;

void Lora_Setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  if (!Transceiver.init(5)) {
    Serial.println("LoRa initialization failed!");
    buzzer_fail_Lora();
    ESP.restart();
  }

  Transceiver.SetAddressH(9);
  Transceiver.SetAddressL(8);
  Transceiver.SetChannel(19);
  Transceiver.SetAirDataRate(ADR_19200);
  Transceiver.SaveParameters(PERMANENT);
  Transceiver.PrintParameters();
  Transceiver.SetMode(EBYTE_MODE_NORMAL);
}

void Lora_receive(void *pvParameters) {
  LoraPacket packet;
  while(1) {
    if(!LoraSender) {
      if(Transceiver.GetStruct(&packet, sizeof(packet))) {
        if(validatePacket(packet)) {
          String data = String(packet.command) + "/" + 
                       String(packet.gatewayId) + "/" +
                       String(packet.penCode) + "/" +
                       String(packet.nodeId) + "/" +
                       String(packet.payload);
          
          if(xSemaphoreTake(xMutex, portMAX_DELAY)) {
            receivedDataList.push_back(data);
            xSemaphoreGive(xMutex);
          }
        }
      }
      vTaskDelay(pdMS_TO_TICKS(10));
    }
    else {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void resetLoRaModule() {
  Transceiver.Reset();
  delay(1000);
  Lora_Setup();
}

bool validatePacket(const LoraPacket& packet) {
  uint8_t calculatedChecksum = 0;
  const uint8_t* data = reinterpret_cast<const uint8_t*>(&packet);
  for(size_t i = 0; i < sizeof(packet) - 1; i++) {
    calculatedChecksum ^= data[i];
  }
  return (calculatedChecksum == packet.checksum);
}