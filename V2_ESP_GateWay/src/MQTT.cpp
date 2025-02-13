#include "MQTT.h"

const char *root_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "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\n"
    "-----END CERTIFICATE-----\n";

String receivedTopic;
String receivedPayload;
SensorData sensorData;
WiFiClient espClient; // Web
// WiFiClientSecure espClient; // Test
PubSubClient client(espClient);

// TEST ----------------------------
// const char *mqtt_broker = "538b23077da5470dbdd03fcfa511e78b.s1.eu.hivemq.cloud";
// const int mqtt_port = 8883; // SSL port
// const char *mqtt_username = "Tule1208";
// const char *mqtt_password = "VanTu1208";

const char* mqtt_broker = "api-trangtrai.nongdanonline.vn";
const int mqtt_port = 1883;  // SSL port
const char* mqtt_username = "bjpdWduGdz";
const char* mqtt_password = "dTIu3b874d";

bool stateList[16] = {false}; // Now you can initialize the array here

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        String clientID = macAddress;
        Serial.print("ClientID: ");
        Serial.println(clientID);
        if (client.connect(clientID.c_str(), mqtt_username, mqtt_password))
        {
            Serial.print("MQTT connected with ClientID: ");
            Serial.println(clientID);

            // Subscribe to control topics if needed
            for (int i = 1; i < 17; i++)
            {
                char topic_ControlRelay[50];
                snprintf(topic_ControlRelay, sizeof(topic_ControlRelay), "%s/controls/%d/command", macAddress, i);
                client.subscribe(topic_ControlRelay);
            }
            char topic_ControlRequestAll[70];
            char topic_ResetWifi[70];
            char topic_ControlRequest[70];
            char topic_PowerRequest[70];
            char topic_ChangeTimeRequest[70];
            char topic_ChangeGatewayIdRequest_Node[70];
            char topic_ChangeGatewayIdRequest[70];
            char topic_clearGatewayIdRequest[70];
            snprintf(topic_ControlRequestAll, sizeof(topic_ControlRequestAll), "%s/controls/request", macAddress);
            snprintf(topic_ResetWifi, sizeof(topic_ResetWifi), "%s/reset-wifi/request", macAddress);
            snprintf(topic_ControlRequest, sizeof(topic_ControlRequest), "%s/controls/+/request", macAddress);
            snprintf(topic_PowerRequest, sizeof(topic_PowerRequest), "%s/power/request", macAddress);
            snprintf(topic_ChangeTimeRequest, sizeof(topic_ChangeTimeRequest), "%s/+/+/changeTime/request", macAddress);
            snprintf(topic_ChangeGatewayIdRequest_Node, sizeof(topic_ChangeGatewayIdRequest_Node), "%s/+/+/changeGatewayId_Node/request", macAddress);
            snprintf(topic_ChangeGatewayIdRequest, sizeof(topic_ChangeGatewayIdRequest), "+/changeGatewayId/request");
            snprintf(topic_clearGatewayIdRequest, sizeof(topic_clearGatewayIdRequest), "+/clearGatewayId/request");
            client.subscribe(topic_ControlRequestAll);
            client.subscribe(topic_ResetWifi);
            client.subscribe(topic_ControlRequest);
            client.subscribe(topic_PowerRequest);
            client.subscribe(topic_ChangeTimeRequest);
            client.subscribe(topic_ChangeGatewayIdRequest_Node);
            client.subscribe(topic_ChangeGatewayIdRequest);
            client.subscribe(topic_clearGatewayIdRequest);
            if (no_GatewayId)
            {
                char responseTopic[50];
                snprintf(responseTopic, sizeof(responseTopic), "newGateway/response");
                char payload[40];
                macAddress.toCharArray(payload, sizeof(payload));

                // Gửi thông điệp phản hồi qua MQTT
                publishMessage(responseTopic, payload);
            }
        }
        else
        {
            // Buzzer ket noi MQTT fail.
            if (WiFi.status() == WL_CONNECTED)
            {
                buzzer_fail_mqtt();
            }
            Serial.print("failed, rc=");
            Serial.print(client.state()); // Print the reason for failure
            if (client.state() == -1)
            {
                Serial.println("Connection refused, incorrect protocol version");
            }
            else if (client.state() == -2)
            {
                Serial.println("Connection refused, identifier rejected");
            }
            else if (client.state() == -3)
            {
                Serial.println("Connection refused, broker unavailable");
            }
            else if (client.state() == -4)
            {
                Serial.println("Connection refused, bad username or password");
            }
            else if (client.state() == -5)
            {
                Serial.println("Connection refused, not authorized");
            }
            Serial.println(" try again in 5 seconds");
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
}

void handleMqttMessage()
{
    Serial.println("Handling MQTT message: " + receivedTopic + " " + receivedPayload);

    if (receivedTopic == String(macAddress) + "/controls/request")
    {
        // Handle get state of all controls
        JsonDocument doc;
        JsonArray array = doc.to<JsonArray>();

        for (int i = 1; i < 17; i++)
        {
            JsonObject obj = array.add<JsonObject>();
            obj["Pin"] = i;
            obj["Value"] = stateList[i - 1] ? 1 : 0;
        }

        char payload[400];
        serializeJson(doc, payload);

        char responseTopic[50];
        snprintf(responseTopic, sizeof(responseTopic), "%s/controls/response", macAddress);
        publishMessage(responseTopic, payload);
    }
    else if (receivedTopic.indexOf(String(macAddress) + "/controls/") != -1 && receivedTopic.endsWith("/request"))
    {
        // Handle get state of a specific control
        int pin = receivedTopic.substring(receivedTopic.indexOf("/controls/") + 10, receivedTopic.lastIndexOf("/")).toInt();

        if (pin >= 1 && pin <= 16)
        {
            char responseTopic[50];
            snprintf(responseTopic, sizeof(responseTopic), "%s/controls/%d/response", macAddress, pin);
            char payload[10];
            snprintf(payload, sizeof(payload), "%d", stateList[pin - 1] ? 1 : 0);
            publishMessage(responseTopic, payload);
        }
    }
    else if (receivedTopic.indexOf(String(macAddress) + "/controls/") != -1 && receivedTopic.endsWith("/command"))
    {
        // Handle command for a specific control
        int pin = receivedTopic.substring(receivedTopic.indexOf("/controls/") + 10, receivedTopic.lastIndexOf("/")).toInt();

        if (pin >= 1 && pin <= 16)
        {
            if (receivedPayload == "0" || receivedPayload == "1")
            {
                bool newState = (receivedPayload == "1");
                stateList[pin - 1] = newState;
                if (receivedPayload == "1")
                {
                    Serial.print("Bật đèn số ");
                    Serial.println(pin);
                }
                else
                {
                    Serial.print("Tắt đèn số ");
                    Serial.println(pin);
                }

                String commandPin = "{\"Pin\":" + String(pin) + ",\"Value\":" + receivedPayload + "}";
                STM_Transmit_Process(commandPin);
                delay(5);
                String controlResponse;
                for (int i = 0; i < 5; i++)
                {
                    STM_Transmit_Process(commandPin);
                    delay(5);
                    controlResponse = STM_Receive_Process();
                    if (controlResponse == receivedPayload)
                        break;
                }
                Serial.print("Command: ");
                Serial.println(commandPin);

                char responseTopic[50];
                snprintf(responseTopic, sizeof(responseTopic), "%s/controls/%d/response", macAddress, pin);

                Serial.print("Control Response: ");
                Serial.println(controlResponse);
                publishMessage(responseTopic, controlResponse.c_str());
            }
        }
    }
    else if (receivedTopic == String(macAddress) + "/reset-wifi/request")
    {
        WiFi_Reset();
    }

    else if (receivedTopic == String(macAddress) + "/power/request")
    {
        String powerCurr;
        for (int i = 0; i < 5; i++)
        {
            STM_Transmit_Process("BB");
            delay(50);
            powerCurr = STM_Receive_Process();
            if (powerCurr != "")
                break;
        }
        char responseTopic[50];

        snprintf(responseTopic, sizeof(responseTopic), "%s/power/response", macAddress);
        delay(30);
        // Tạo nội dung phản hồi
        char payload[20];

        snprintf(payload, sizeof(payload), "%s", powerCurr);

        // Gửi thông điệp phản hồi
        publishMessage(responseTopic, payload);
    }
    else if (receivedTopic.startsWith(String(macAddress) + "/") && receivedTopic.endsWith("/changeTime/request"))
    {
        // Chuyển đổi topic từ String sang char[] để phân tích
        char topicBuffer[100];
        receivedTopic.toCharArray(topicBuffer, sizeof(topicBuffer));

        // Phân tách các thành phần trong topic
        char *token = strtok(topicBuffer, "/");
        int tokenIndex = 0;
        String penCodeSend, NodeIdSend;

        while (token != NULL)
        {
            tokenIndex++;
            if (tokenIndex == 2) // Phần tử thứ 2 sau địa chỉ MAC là penCode
            {
                penCodeSend = token;
            }
            else if (tokenIndex == 3) // Phần tử thứ 3 là NodeId
            {
                NodeIdSend = token;
            }
            token = strtok(NULL, "/");
        }

        if (penCodeSend.length() > 0 && NodeIdSend.length() > 0)
        {
            String timeChange = receivedPayload;

            // Reset và khởi động lại LoRa
            LoraSender = true;
            resetLoRaModule();

            LoraPacket packet;
            snprintf(packet.command, sizeof(packet.command), "time");
            snprintf(packet.gatewayId, sizeof(packet.gatewayId), "%s", macAddress.c_str());
            packet.penCode = penCodeSend.toInt();
            packet.nodeId = NodeIdSend.toInt();
            snprintf(packet.payload, sizeof(packet.payload), "%s", timeChange.c_str());
            packet.calculateChecksum();
            
            Transceiver.SendStruct(&packet, sizeof(packet));

            // Chờ phản hồi
            bool ackReceived = false;
            unsigned long startTime = millis();
            while (millis() - startTime < 3000) {
                LoraPacket response;
                if (Transceiver.GetStruct(&response, sizeof(response))) {
                    if (strcmp(response.command, "BCK") == 0 &&
                        strcmp(response.gatewayId, macAddress.c_str()) == 0 &&
                        response.penCode == penCodeSend.toInt() &&
                        response.nodeId == NodeIdSend.toInt()) {
                        ackReceived = true;
                        break;
                    }
                }
                delay(10);
            }

            // Gửi phản hồi qua MQTT
            char responseTopic[100];
            snprintf(responseTopic, sizeof(responseTopic), "%s/%s/%s/changeTime/response",
                     macAddress.c_str(), penCodeSend.c_str(), NodeIdSend.c_str());

            char payload[10];
            snprintf(payload, sizeof(payload), "%d", ackReceived ? 1 : 0);
            publishMessage(responseTopic, payload);

            // Đặt lại LoRa về chế độ nhận
            LoraSender = false;
            resetLoRaModule();
        }
    }
    else if (receivedTopic.endsWith("/changeGatewayId/request"))
    {
        // Lấy macAddress từ topic bằng cách loại bỏ phần đuôi "/changeGatewayId/request"
        String receivedMacAddress = receivedTopic.substring(0, receivedTopic.length() - String("/changeGatewayId/request").length());

        // So sánh macAddress nhận được với macAddress của thiết bị
        if (receivedMacAddress == macAddress)
        {
            String newGatewayId = receivedPayload;
            macAddress = newGatewayId;
            saveToEEPROM(macAddress);
            char responseTopic[50];
            snprintf(responseTopic, sizeof(responseTopic), "%s/changeGatewayId/response", macAddress);
            // Tạo nội dung phản hồi
            char payload[5];
            Serial.println("Change Gateway ID to: " + newGatewayId);
            snprintf(payload, sizeof(payload), "1");

            // Gửi thông điệp phản hồi qua MQTT
            publishMessage(responseTopic, payload);
            ESP.restart();
        }
        else
        {
            Serial.println("Received topic for another device. Ignoring.");
        }
    }

    else if (receivedTopic.endsWith("/clearGatewayId/request"))
    {
        // Lấy macAddress từ topic bằng cách loại bỏ phần đuôi "/changeGatewayId/request"
        String receivedMacAddress = receivedTopic.substring(0, receivedTopic.length() - String("/clearGatewayId/request").length());

        // So sánh macAddress nhận được với macAddress của thiết bị
        if (receivedMacAddress == macAddress)
        {
            String newGatewayId = receivedPayload;
            macAddress = newGatewayId;
            clearEEPROM();
            char responseTopic[50];
            snprintf(responseTopic, sizeof(responseTopic), "%s/clearGatewayId/response", macAddress);
            // Tạo nội dung phản hồi
            char payload[5];
            Serial.println("clear Gateway ID");
            snprintf(payload, sizeof(payload), "1");

            // Gửi thông điệp phản hồi qua MQTT
            publishMessage(responseTopic, payload);
            ESP.restart();
        }
        else
        {
            Serial.println("Received topic for another device. Ignoring.");
        }
    }

    else if (receivedTopic.startsWith(String(macAddress) + "/") && receivedTopic.endsWith("/changeGatewayId_Node/request")) {
        char topicBuffer[100];
        receivedTopic.toCharArray(topicBuffer, sizeof(topicBuffer));
        String macAddressForNode = receivedPayload;
        char *token = strtok(topicBuffer, "/");
        int tokenIndex = 0;
        String penCodeSend, NodeIdSend;

        while (token != NULL) {
            tokenIndex++;
            if (tokenIndex == 2) penCodeSend = token;
            else if (tokenIndex == 3) NodeIdSend = token;
            token = strtok(NULL, "/");
        }

        if (penCodeSend.length() > 0 && NodeIdSend.length() > 0) {
            LoraSender = true;
            
            // Gửi gói tin qua EBYTE
            LoraPacket packet;
            snprintf(packet.command, sizeof(packet.command), "rsID");
            packet.penCode = penCodeSend.toInt();
            packet.nodeId = NodeIdSend.toInt();
            snprintf(packet.payload, sizeof(packet.payload), "%s", macAddressForNode.c_str());
            packet.calculateChecksum();
            
            Transceiver.SendStruct(&packet, sizeof(packet));

            // Chờ phản hồi
            bool ackReceived = false;
            unsigned long startTime = millis();
            while (millis() - startTime < 3000) {
                LoraPacket response;
                if (Transceiver.GetStruct(&response, sizeof(response))) {
                    if (strcmp(response.command, "ACK") == 0 &&
                        strcmp(response.payload, macAddressForNode.c_str()) == 0 &&
                        response.penCode == penCodeSend.toInt() &&
                        response.nodeId == NodeIdSend.toInt()) {
                        ackReceived = true;
                        break;
                    }
                }
                delay(10);
            }

            // Gửi phản hồi MQTT
            char responseTopic[100];
            snprintf(responseTopic, sizeof(responseTopic), "%s/%s/%s/changeGatewayId_Node/response", 
                    macAddress.c_str(), penCodeSend.c_str(), NodeIdSend.c_str());
            char payload[10];
            snprintf(payload, sizeof(payload), "%d", ackReceived);
            publishMessage(responseTopic, payload);

            LoraSender = false;
        }
    }
}
void callback(char *topic, byte *payload, unsigned int length)
{
    receivedTopic = String(topic);
    receivedPayload = String((char *)payload, length);
    handleMqttMessage();
}

void MQTT_Setup()
{
    //espClient.setCACert(root_ca);
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
}

void publishMessage(const char *topic, const char *payload)
{
    if (client.connected())
    {
        client.publish(topic, payload);
        Serial.println("Published message: " + String(payload) + " to topic: " + String(topic));
    }
    else
    {
        Serial.println("MQTT client not connected, message not sent.");
    }
}

void processData(const String &data)
{
    // Parse input data

    // Tách giá trị gatewayId
    int startIndex = data.indexOf("gatewayId:") + 10; // 10 là độ dài chuỗi "gatewayId:"
    int endIndex = data.indexOf(';', startIndex);
    sensorData.GatewayId = data.substring(startIndex, endIndex);

    // Tách các giá trị khác
    startIndex = data.indexOf("penCode:") + 8;
    endIndex = data.indexOf(';', startIndex);
    sensorData.penCode = data.substring(startIndex, endIndex).toInt();

    startIndex = data.indexOf("nodeId:") + 7;
    endIndex = data.indexOf(';', startIndex);
    sensorData.nodeId = data.substring(startIndex, endIndex).toInt();

    startIndex = data.indexOf("Temp:") + 5;
    endIndex = data.indexOf(';', startIndex);
    sensorData.temp = data.substring(startIndex, endIndex).toFloat();

    startIndex = data.indexOf("Hum:") + 4;
    endIndex = data.indexOf(';', startIndex);
    sensorData.hum = data.substring(startIndex, endIndex).toFloat();

    startIndex = data.indexOf("NH3:") + 4;
    endIndex = data.indexOf(';', startIndex);
    sensorData.nh3 = data.substring(startIndex, endIndex).toFloat();

    startIndex = data.indexOf("H2S:") + 4;
    sensorData.h2s = data.substring(startIndex).toFloat();
    Serial.print("MacAddress: ");
    Serial.print(macAddress);
    Serial.print(" ----- GatewayId: ");
    Serial.println(sensorData.GatewayId);
    if (sensorData.GatewayId == macAddress)
    {

        // Create JSON object
        JsonDocument doc;
        JsonArray array = doc.to<JsonArray>();

        // Add sensor data in the specified format
        JsonObject tempObj = array.createNestedObject();

        tempObj["Pin"] = 1;
        tempObj["Value"] = float(sensorData.temp);

        JsonObject humObj = array.createNestedObject();
        humObj["Pin"] = 2;
        humObj["Value"] = float(sensorData.hum);

        JsonObject nh3Obj = array.createNestedObject();
        nh3Obj["Pin"] = 3;
        nh3Obj["Value"] = float(sensorData.nh3);

        JsonObject h2sObj = array.createNestedObject();
        h2sObj["Pin"] = 4;
        h2sObj["Value"] = float(sensorData.h2s);

        LoraSender = true;
        resetLoRaModule();
        
        LoraPacket ackPacket;
        snprintf(ackPacket.command, sizeof(ackPacket.command), "OK");
        snprintf(ackPacket.gatewayId, sizeof(ackPacket.gatewayId), "%s", macAddress.c_str());
        ackPacket.penCode = sensorData.penCode;
        ackPacket.nodeId = sensorData.nodeId;
        ackPacket.calculateChecksum();

        LoraSender = true;
        Transceiver.SendStruct(&ackPacket, sizeof(ackPacket));
        LoraSender = false;
        resetLoRaModule();

        char payload[256];
        serializeJson(doc, payload);
        char topic[50];
        snprintf(topic, sizeof(topic), "%s/%s/%s/sensors/response", macAddress, String(sensorData.penCode), String(sensorData.nodeId));
        publishMessage(topic, payload);
    }
    else
    {
        Serial.println("Server ID không trùng khớp");
    }
}

void MQTT_Process(void *)
{
    while (1)
    {
        if (!client.connected())
            reconnect();
        client.loop();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void MQTT_Send_SensorValue(void *)
{
    while (1)
    {
        if (!receivedDataList.empty())
        {
            String data = receivedDataList.front();
            processData(data);
            receivedDataList.erase(receivedDataList.begin());
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}