#include "mWebserver.h"
#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;
void webserverHandle(void *pvParameters)
{
  Serial.print("webserverHandle running on core ");
  Serial.println(xPortGetCoreID());
  uint32_t timer = millis();
  for (;;)
  {
    delay(10);
    loopWebserver();
    if (millis() - timer > 3000)
    {
      udp.beginPacket("255.255.255.255", 7878);
      delay(10);
      udp.println(String("MAC: ") + WiFi.macAddress());
      delay(10);
      udp.endPacket();
      delay(10);

      timer = millis();
    }
  }
}
void setupMServer()
{
  setupWebserver();
  xTaskCreatePinnedToCore(
      webserverHandle,   /* Task function. */
      "webserverHandle", /* name of task. */
      50000,             /* Stack size of task */
      NULL,              /* parameter of the task */
      0,                 /* priority of the task */
      NULL,    /* Task handle to keep track of created task */
      0);                /* pin task to core 0 */
}

void loopMServer()
{
}