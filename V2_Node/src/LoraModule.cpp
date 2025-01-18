#include "LoraModule.h"

String gatewayId;
int addrGatewayId = 4;
bool LoraSender = false;
uint32_t waitDuration = 30 * 1000000; // Thời gian chờ mặc định là 30 giây

// Khởi tạo đối tượng LoRa E32
LoRa_E32 e32ttl100(&Serial2);

void LoraSetup() {
    e32ttl100.begin();
    Serial.println("LoRa E32 init succeeded.");
    e32ttl100.setMode(MODE_0_NORMAL); // Chế độ hoạt động bình thường
}

void sendSensorData(String gatewayId, int penCode, int nodeId, float t, float h, float nh3, float h2s) {
    beginSend();
    bool ackReceived = false;
    int count = 0;

    while (!ackReceived && count <= 3) {
        String data = "gatewayId:" + gatewayId + "; penCode:" + String(penCode) + "; nodeId:" + String(nodeId) +
                      "; Temp:" + String(t) + "; Hum:" + String(h) + "; NH3:" + String(nh3) + "; H2S:" + String(h2s);

        ResponseStatus rs = e32ttl100.sendMessage(data);
        if (rs.code == 1) {
            unsigned long startTime = millis();
            while (millis() - startTime < 5000) {
                if (e32ttl100.available() > 1) {
                    ResponseContainer rc = e32ttl100.receiveMessage();
                    String response = rc.data;
                    if (response.startsWith("OK/")) {
                        // Xử lý phản hồi
                        String receivedMac = response.substring(3, response.indexOf('/', 3));
                        int receivedPenCode = response.substring(response.indexOf('/', 3) + 1, response.lastIndexOf('/')).toInt();
                        int receivedNodeId = response.substring(response.lastIndexOf('/') + 1).toInt();

                        if (receivedMac == gatewayId && receivedPenCode == penCode && receivedNodeId == nodeId) {
                            digitalWrite(PB10, HIGH);
                            delay(200);
                            digitalWrite(PB10, LOW);
                            ackReceived = true;
                            break;
                        }
                    }
                }
            }
        }
        count++;
    }
    endSend();
}

bool receiveLoraData(String &receivedData) {
    if (!LoraSender) {
        if (e32ttl100.available() > 1) {
            ResponseContainer rc = e32ttl100.receiveMessage();
            receivedData = rc.data;
            return true;
        }
        return false;
    } else {
        return false;
    }
}

void processReceivedData(String &data) {
    // Xử lý dữ liệu nhận được tương tự như code gốc
    // ...
}

void beginSend(void) {
    LoraSender = true;
    e32ttl100.setMode(MODE_0_NORMAL);
}

void endSend(void) {
    e32ttl100.setMode(MODE_0_NORMAL);
    LoraSender = false;
}