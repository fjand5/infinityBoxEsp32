#include "box.h"
TaskHandle_t boxTask;
void boxHandle( void * pvParameters ){
  box.settup();
  for(;;){
    box.beforeService();
    box.service();
    box.affterService();
  } 
}
void setTimer(uint32_t timer){
  box.setTimer(timer);
}
void nextMode(){
  box.nextMode();
}
void previousMode(){
  box.previousMode();
}
void changeSpeed(uint16_t spd){
  box.changeSpeed(spd);
}
void changeBrightness(uint16_t bgh){
  box.changeBrightness(bgh);
}
void pauseBox(){
  box.pause();
}
void resumeBox(){
  box.resume();
}
void onBox(){
  box.onBox();
}
void offBox(){
  box.offBox();
}
void onTimer(){
  box.onTimer();
}
void offTimer(){
  box.offTimer();
}
void setupBox() {


  // parameters: index, start, stop, mode, color, speed, reverse



    xTaskCreatePinnedToCore(
                    boxHandle,   /* Task function. */
                    "boxHandle",     /* name of task. */
                    30000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &boxTask,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */  
}

void loopBox() {
}