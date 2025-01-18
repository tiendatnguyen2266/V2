#include "getTime.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600; // Múi giờ UTC+7 (cho Việt Nam)
const int daylightOffset_sec = 0;    // Không có giờ mùa hè
int hourStart, minStart, secStart;
int hourEnd, minEnd, secEnd;
void getTime_Setup()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void getPowerPerMinute(void *)
{
  int previousHour = -1;
  while (1)
  {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
      Serial.println("Không lấy được thời gian.");
      cannot_get_time();
    }
    else
    {
      char timeString[20];
      strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);
      Serial.println(timeString);
      if (timeinfo.tm_min != previousHour)
      {
        hourStart = hourEnd;
        minStart = minEnd;
        secStart = secEnd;
        hourEnd = timeinfo.tm_hour;
        minEnd = timeinfo.tm_min;
        secEnd = timeinfo.tm_sec;
        String PowerReceive;
        for (int i = 0; i < 5; i++)
        {
          STM_Transmit_Process("AA");
          delay(50);
          PowerReceive = STM_Receive_Process();
          if (PowerReceive != "")
            break;
        }
        previousHour = timeinfo.tm_min;
        char responseTopic[70];
        const char *macCharArray = macAddress.c_str();
        snprintf(responseTopic, sizeof(responseTopic), "%s/power-average/response", macCharArray);
        // Tạo nội dung phản hồi
        char beginTime[30], endTime[30];
        snprintf(beginTime, sizeof(beginTime), "%04d-%02d-%02dT%02d:%02d:%02d",
                 timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                 hourStart, minStart, secStart);
        snprintf(endTime, sizeof(endTime), "%04d-%02d-%02dT%02d:%02d:%02d",
                 timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                 hourEnd, minEnd, secEnd);

        StaticJsonDocument<256> doc;
        doc["beginTime"] = beginTime;
        doc["endTime"] = endTime;
        doc["Data"] = PowerReceive;

        char payload[512];
        serializeJson(doc, payload);

        publishMessage(responseTopic, payload);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}