#include "mWebserver.h"
#include <WiFi.h>
void webserverHandle(void *pvParameters)
{
  // log_d("webserverHandle running on core: %d ",xPortGetCoreID());

  setupWebserver();
  uint32_t timer = millis();
  while (1)
  {
    loopWebserver();
    // if (millis() - timer > 1000)
    // {
    //   log_d("webserverHandle loop on core: %d ", xPortGetCoreID());
    //   timer = millis();
    // }
  }
}
void setupMServer()
{
  xTaskCreatePinnedToCore(
      webserverHandle,   /* Task function. */
      "webserverHandle", /* name of task. */
      10000,             /* Stack size of task */
      NULL,              /* parameter of the task */
      1,                 /* priority of the task */
      NULL,              /* Task handle to keep track of created task */
      0);                /* pin task to core 0 */
}

void loopMServer()
{
}