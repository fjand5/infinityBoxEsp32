
#include "Arduino.h"

#include "lib/box/handleBox.h"
#include "lib/webserver/handleWebserver.h"
#include "src/renderUI/rendeUI.h"
void setup() {
  Serial.begin(115200);
  setupConfig();
  setupMServer();
  setupBox();
  setupRender();
}

void loop() {
}