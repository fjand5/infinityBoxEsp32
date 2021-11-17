#include "mWebserver.h"
#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;
void webserverHandle(void *pvParameters)
{
  // log_d("webserverHandle running on core: %d ",xPortGetCoreID());
  
  setupWebserver();
  uint32_t timer = millis();
  for (;;)
  {
    loopWebserver();
    if (millis() - timer > 3000 
    &&  webSocket.connectedClients() == 0
    )
    {
      udp.beginPacket("255.255.255.255", 7878);
      udp.println(String("MAC: ") + WiFi.macAddress());
      udp.endPacket();
      log_d("beginPacket");
      timer = millis();
    }
  }
}
void setupMServer()
{
  xTaskCreatePinnedToCore(
      webserverHandle,   /* Task function. */
      "webserverHandle", /* name of task. */
      50000,             /* Stack size of task */
      NULL,              /* parameter of the task */
      1,                 /* priority of the task */
      NULL,    /* Task handle to keep track of created task */
      0);                /* pin task to core 0 */
}

void loopMServer()
{
}