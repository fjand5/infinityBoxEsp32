# 1 "C:\\Users\\Luat\\AppData\\Local\\Temp\\tmp7per7i8t"
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