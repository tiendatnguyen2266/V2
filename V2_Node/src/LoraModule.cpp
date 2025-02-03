#include "LoraModule.h"

// Khởi tạo UART và LoRa
HardwareSerial Serial2(RXD2, TXD2);
EBYTE Transceiver(&Serial2, PIN_M0, PIN_M1, PIN_AUX);


String gatewayId;
uint32_t waitDuration = 30000; // Thời gian chờ mặc định là 30 giây


void LoraSetup() {
  Serial2.begin(9600);
  pinMode(PIN_AUX, INPUT);
  
  if (!Transceiver.init()) {
    Serial.println("LoRa initialization failed!");
    while(1);
  }
  
  // Cấu hình tham số cho LoRa
  Transceiver.SetAddressH(0);
  Transceiver.SetAddressL(1);
  Transceiver.SetChannel(15);
  Transceiver.SetAirDataRate(ADR_2400);
  Transceiver.SaveParameters(PERMANENT);
  
  Serial.println("LoRa initialized successfully!");
}

// Hàm gửi
void sendSensorData(String gatewayId, int penCode, int nodeId, float t, float h, float nh3, float h2s) {
  SensorData data;
  gatewayId.toCharArray(data.gatewayId, 16);
  data.penCode = penCode;
  data.nodeId = nodeId;
  data.t = t;
  data.h = h;
  data.nh3 = nh3;
  data.h2s = h2s;

  bool ackReceived = false;
  int attempts = 0;
  
  while (!ackReceived && attempts < 3) {
    beginSend();
    Transceiver.SendStruct(&data, sizeof(data));
    
    // Chờ phản hồi trong 5s
    unsigned long start = millis();
    while (millis() - start < 5000) {
      if (Transceiver.available()) {
        AckData ack;
        if (Transceiver.GetStruct(&ack, sizeof(ack))) {
          if (strcmp(ack.status, "OK") == 0 && 
              strcmp(ack.gatewayId, gatewayId.c_str()) == 0 &&
              ack.penCode == penCode && 
              ack.nodeId == nodeId) {
            ackReceived = true;
            // Kích hoạt buzzer
            digitalWrite(PB10, HIGH);
            delay(200);
            digitalWrite(PB10, LOW);
            break;
          }
        }
      }
    }
    attempts++;
    endSend();
  }
}

// Hàm nhận
bool receiveLoraData(String &receivedData) {
  if (Transceiver.available()) {
    SensorData data;
    if (Transceiver.GetStruct(&data, sizeof(data))) {
      // Chuyển struct thành chuỗi để xử lý
      receivedData = "gatewayId:" + String(data.gatewayId) 
                   + "; penCode:" + String(data.penCode)
                   + "; nodeId:" + String(data.nodeId)
                   + "; Temp:" + String(data.t)
                   + "; Hum:" + String(data.h)
                   + "; NH3:" + String(data.nh3)
                   + "; H2S:" + String(data.h2s);
      return true;
    }
  }
  return false;
}

// Hàm xử lý dữ liệu nhận
void processReceivedData(String &data) {
  if (data.startsWith("time/")) {
    // Xử lý gói tin "time/"
    int firstSlash = data.indexOf('/');
    int secondSlash = data.indexOf('/', firstSlash + 1);
    int thirdSlash = data.indexOf('/', secondSlash + 1);
    int fourthSlash = data.indexOf('/', thirdSlash + 1);

    String receivedMacAddress = data.substring(firstSlash + 1, secondSlash);
    String receivedPenCode = data.substring(secondSlash + 1, thirdSlash);
    String receivedNodeId = data.substring(thirdSlash + 1, fourthSlash);
    String timeValue = data.substring(fourthSlash + 1);

    int timeChange = timeValue.toInt();

    if (receivedMacAddress == gatewayId && penCode == receivedPenCode.toInt() && nodeId == receivedNodeId.toInt()) {
      if (timeChange > 0) {
        beginSend();
        AckData ack;
        strncpy(ack.status, "ACK", 4);
        strncpy(ack.gatewayId, gatewayId.c_str(), 16);
        ack.penCode = penCode;
        ack.nodeId = nodeId;
        Transceiver.SendStruct(&ack, sizeof(ack));
        endSend();

        EEPROMLib::writeInt(32, timeChange);
        waitDuration = timeChange * 1000000; // Chuyển đổi thành micro giây
      }
    }
  } else if (data.startsWith("rsID:")) {
    // Xử lý gói tin "rsID:"
    digitalWrite(PB10, HIGH);
    delay(200);
    digitalWrite(PB10, LOW);
  }
}

// Hàm reset module LoRa
void resetLoRaModule() {
  Transceiver.Reset();
}

// Hàm bắt đầu gửi dữ liệu
void beginSend() {
  Transceiver.SetMode(EBYTE_MODE_NORMAL);
}

// Hàm kết thúc gửi dữ liệu
void endSend() {
  Transceiver.SetMode(EBYTE_MODE_NORMAL);
}