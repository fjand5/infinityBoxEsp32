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
  box.pause();
}
void resumeBox()
{
  box.resume();
}
void onBox()
{
  box.onBox();
}
void offBox()
{
  box.offBox();
}
void onTimer()
{
  box.onTimer();
}
void offTimer()
{
  box.offTimer();
}
void onReact()
{
  box.setReacMusic(true);
}
void offReact()
{
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
  rmt_write_sample(RMT_CHANNEL, pixels, numBytes, false); // channel 0
}
void boxHandle(void *pvParameters)
{
  Serial.print("boxHandle running on core ");
  Serial.println(xPortGetCoreID());
  Serial.println("box setup done");
  for (;;)
  {
    if (box.beforeService([]()
                          { return getValByFreq(onChangeBeat); }))
      box.service();
    box.affterService();
  }
}
void setupBox()
{
  setupMIC();

  rmt_tx_int(RMT_CHANNEL, box.getPin());
  box.setCustomShow(rmtShow);
  box.settup();

  if (getValue("on_off_tgl") != "true")
  {
    offBox();
    Serial.println("offBox");
  }
  else
  {
    onBox();
    Serial.println("onBox");
  }
  setTimer(getValue("timer_sld", "5").toInt() * 1000);
  getValue("timer_tgl", "false") == "true" ? onTimer() : offTimer();
  changeBrightness(getValue("brightness_sld", "50").toInt());
  // box.setSymmetry(box.getSymmetricNumber(getValue("cur_sym", box.getSymmetricString(SYM_TEST))));
  if (!checkKey("react_music"))
    setValue("react_music", "false");
  if (getValue("react_music", "false") == "true")
  {
    onReact();
  }
  else
  {
    offReact();
  }

  setSoundEffectMode(getValue("cur_music_mode", "1").toInt(), &box);

  changeMode(getValue("current_mode", "12").toInt());

  box.setColor1(stringToColor(getValue("color1_inp", "#ff0000")));
  box.setColor2(stringToColor(getValue("color2_inp", "#00ff00")));
  box.setColor3(stringToColor(getValue("color3_inp", "#0000ff")));
resumeBox();
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