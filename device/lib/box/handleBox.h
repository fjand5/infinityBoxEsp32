#pragma once
#include "box.h"
#include "mic.h"
#include "../helper.h"

void setTimer(uint32_t timer)
{
  box.setTimer(timer);
}
void changeMode(int mode)
{
  box.changeMode(mode);
}
void nextMode()
{
  box.nextMode();
}
void previousMode()
{
  box.previousMode();
}
void changeSpeed(uint16_t spd)
{
  box.changeSpeed(spd);
}
void changeBrightness(uint16_t bgh)
{
  box.changeBrightness(bgh);
}
void pauseBox()
{
  Serial.println(__func__);
  box.pause();
}
void resumeBox()
{
  Serial.println(__func__);
  box.resume();
}
void onBox()
{
  Serial.println(__func__);
  box.onBox();
}
void offBox()
{
  Serial.println(__func__);
  box.offBox();
}
void onTimer()
{
  Serial.println(__func__);
  box.onTimer();
}
void offTimer()
{
  Serial.println(__func__);
  box.offTimer();
}

bool lastTimerState;
void onReact()
{
  Serial.println(__func__);
  lastTimerState= box.isTimerOn();
  box.setReacMusic(true);
}
void offReact()
{
  Serial.println(__func__);
  lastTimerState ? box.onTimer(): box.offTimer();
  box.setReacMusic(false);
}
void onChangeBeat(double val, double freq)
{
  box.onChangeBeat(val, freq);
}
void rmtShow()
{
  uint8_t *pixels = box.getPixels();
  uint16_t numBytes = box.getNumBytes() + 1;
  rmt_write_sample(RMT_CHANNEL, pixels, numBytes, true); // channel 0
}
void boxHandle(void *pvParameters)
{
  Serial.print("boxHandle running on core ");
  Serial.println(xPortGetCoreID());
  Serial.println("box setup done");

  // uint32_t preTime = millis();
  for (;;)
  {
    // preTime = millis();
    if (box.beforeService([]()
                          { return getValByFreq(onChangeBeat); }))
      box.service();
    box.affterService();
    // uint32_t delta = millis() - preTime;
    // log_e("%s",delta);
  }
}
void setupBox()
{
  setupMIC();

  rmt_tx_int(RMT_CHANNEL, box.getPin());
  box.setCustomShow(rmtShow);
  box.settup();
  
  box.setColor1(stringToColor(getValue("color1_inp", "#ff0000")));
  box.setColor2(stringToColor(getValue("color2_inp", "#00ff00")));
  box.setColor3(stringToColor(getValue("color3_inp", "#0000ff")));
  
  resumeBox();
  setValue("pause_tgl", "true");
  getValue("on_off_tgl", "false") == "true" ? onBox() : offBox();
  setTimer(getValue("timer_sld", "5").toInt() * 1000);
  getValue("timer_tgl", "false") == "true" ? onTimer() : offTimer();
  changeBrightness(getValue("brightness_sld", "50").toInt());
  if (getValue("react_music", "false") == "true")
  {
    
    onReact();
    setSoundEffectMode(SE_VU_METER_COLUMN, &box);
  }
  else
  {
    offReact();
    changeMode(getValue("current_mode", "12").toInt());
  }


  xTaskCreatePinnedToCore(
      boxHandle,            /* Task function. */
      "boxHandle",          /* name of task. */
      50000,                /* Stack size of task */
      NULL,                 /* parameter of the task */
      configMAX_PRIORITIES, /* priority of the task */
      NULL,                 /* Task handle to keep track of created task */
      1);                   /* pin task to core 0 */
}

void loopBox()
{
}