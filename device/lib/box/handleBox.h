#pragma once
#include "box.h"
#include "mic.h"
TaskHandle_t boxTask;

void setTimer(uint32_t timer){
  box.setTimer(timer);
}
void changeMode(int mode){
  box.changeMode(mode);
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
void onReact(){
  box.setReacMusic(true);
}
void offReact(){
  box.setReacMusic(false);
}
void onChangeBeat(double val, double freq){
  box.onChangeBeat(val, freq);
}
void boxHandle( void * pvParameters ){
  Serial.print("boxHandle running on core ");
  Serial.println(xPortGetCoreID());
  setupMIC();
  box.settup();
  for(;;){
    if(box.beforeService([](){
      return getValByFreq(onChangeBeat);
    })) 
    box.service();
    box.affterService();
  } 
}
void setupBox() {


  // parameters: index, start, stop, mode, color, speed, reverse



    xTaskCreatePinnedToCore(
                    boxHandle,   /* Task function. */
                    "boxHandle",     /* name of task. */
                    30000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    configMAX_PRIORITIES,           /* priority of the task */
                    &boxTask,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */  
}

void loopBox() {
}