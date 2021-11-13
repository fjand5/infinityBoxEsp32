# 1 "C:\\Users\\Luat\\AppData\\Local\\Temp\\tmpi6ky56rd"
#include <Arduino.h>
# 1 "C:/Users/Luat/Desktop/myGit/GitHub/infinityBoxEsp32/device/infinityBoxEsp32.ino"

#include "Arduino.h"

#include "lib/box/handleBox.h"
#include "lib/webserver/handleWebserver.h"
#include "src/renderUI/rendeUI.h"
#include "lib/button/button.h"
void setup();
void loop();
#line 9 "C:/Users/Luat/Desktop/myGit/GitHub/infinityBoxEsp32/device/infinityBoxEsp32.ino"
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