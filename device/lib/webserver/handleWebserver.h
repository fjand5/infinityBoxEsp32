#include "mWebserver.h"
#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;
TaskHandle_t webserverTask;
void webserverHandle(void *pvParameters)
{
  Serial.print("webserverHandle running on core ");
  Serial.println(xPortGetCoreID());
  setupWebserver();
  uint32_t timer = millis();
  for (;;)
  {
    delay(1);
    loopWebserver();
    if (millis() - timer > 3000)
    {
      udp.beginPacket("255.255.255.255", 7878);
      udp.println(String("MAC: ") + WiFi.macAddress());
      udp.endPacket();
      timer = millis();
    }
  }
}
void setupMServer()
{

  xTaskCreatePinnedToCore(
      webserverHandle,   /* Task function. */
      "webserverHandle", /* name of task. */
      30000,             /* Stack size of task */
      NULL,              /* parameter of the task */
      2,                 /* priority of the task */
      &webserverTask,    /* Task handle to keep track of created task */
      0);                /* pin task to core 0 */
}

void loopMServer()
{
}