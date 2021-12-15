
#include "Arduino.h"

#include "lib/box/handleBox.h"
#include "lib/webserver/handleWebserver.h"
#include "src/renderUI/rendeUI.h"
#include "lib/button/button.h"

void setup() {
  // Serial.begin(115200);
  delay(100);
  log_d("BOOTED...");
  setupConfig();
  setupBox();
  setupButton();
  setupMServer();
  setupRender();
  log_d("setup running on core: %d",xPortGetCoreID());
  setValue("version","1.5.4");
  vTaskDelete(NULL);
}

void loop() {
}