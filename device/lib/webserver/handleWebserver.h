#include "mWebserver.h"
TaskHandle_t webserverTask;
void webserverHandle( void * pvParameters ){
setupWebserver();
  for(;;){
    delay(1);
    loopWebserver();
  } 
}
void setupMServer() {

    xTaskCreatePinnedToCore(
                    webserverHandle,   /* Task function. */
                    "webserverHandle",     /* name of task. */
                    30000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &webserverTask,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */  
}

void loopMServer() {
}