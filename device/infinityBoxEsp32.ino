
#include "Arduino.h"

#include "lib/box/handleBox.h"
#include "lib/webserver/handleWebserver.h"
#include "src/renderUI/rendeUI.h"
#include "lib/button/button.h"

void setup() {
  Serial.begin(115200);
  delay(100);
  setupConfig();
  setupBox();
  setupButton();
  setupMServer();
  setupRender();
  Serial.print("setup running on core ");
  Serial.println(xPortGetCoreID());
  vTaskDelete(NULL);
}

void loop() {
}