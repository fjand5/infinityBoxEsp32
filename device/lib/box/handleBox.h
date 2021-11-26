#pragma once
#include "box.h"
#include "mic.h"
#include "../helper.h"
#include "./utils.h"
#define DEFAULT_TIMER 10
#define DEFAULT_BRIGHTNESS 50
#define DEFAULT_MODE FX_MODE_RAINBOW_CYCLE

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

int lastTimerState = -1;
void onReact()
{
  lastTimerState = box.isTimerOn();
  box.setReacMusic(true);
}
void offReact()
{
  // Nếu lastTimerState đã được gán giá trị.
  if (lastTimerState >= 0)
    lastTimerState ? box.onTimer() : box.offTimer();
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

  uint8_t *pixels2Show;

  uint16_t numBytes2Show;
  if (box.isPatternMode())
  {
    uint8_t *patternBuffer = box.getPatternBuffer();
    numBytes2Show = (numBytes - 1) / 2;
    for (uint16_t i = 0; i < numBytes2Show; i++)
    {
      uint8_t pixel1 = pixels[i] / 2;
      uint8_t pixel2 = pixels[i + numBytes2Show] / 2;
      patternBuffer[i] = pixel1 + pixel2;
    }
    pixels2Show = patternBuffer;
  }
  else
  {
    pixels2Show = pixels;
    numBytes2Show = numBytes;
  }
  rmt_write_sample(RMT_CHANNEL, pixels2Show, numBytes2Show, true); // channel 0
}
void boxHandle(void *pvParameters)
{
  log_d("boxHandle running on core: %d", xPortGetCoreID());

  rmt_tx_int(RMT_CHANNEL, box.getPin());
  box.setCustomShow(rmtShow);
  box.settup();

  box.setColor1(stringToColor(getValue("color1_inp", "#ff0000")));
  box.setColor2(stringToColor(getValue("color2_inp", "#00ff00")));
  box.setColor3(stringToColor(getValue("color3_inp", "#0000ff")));

  resumeBox();
  onBox();
  setValue("pause_tgl", "true");
  setTimer(getValue("timer_sld", String(DEFAULT_TIMER)).toInt());
  changeBrightness(getValue("brightness_sld", String(DEFAULT_BRIGHTNESS)).toInt());

  if (getValue("react_music", "false") == "true")
  {
    onReact();
    // setSymmetry(&box, SYM_VERTEX);
    setSoundEffectMode(getValue("cur_music_mode").toInt(), &box);
  }
  else
  {
    offReact();
    changeMode(getValue("current_mode", String(DEFAULT_MODE)).toInt());
  }
  if (getValue("pattern_mode", "false") == "true")
  {
    box.setPatternEffect(true);
  }
  else
  {
    box.setPatternEffect(false);
  }
  delay(1000);
  String tmp = getValue("timer_tgl", "true");
  log_d("===============================================tmp: %s", tmp.c_str());
  tmp == "true" ? onTimer() : offTimer();
  // setOnSaveConfigFile(&box);

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

  xTaskCreatePinnedToCore(
      boxHandle,            /* Task function. */
      "boxHandle",          /* name of task. */
      60000,                /* Stack size of task */
      NULL,                 /* parameter of the task */
      configMAX_PRIORITIES, /* priority of the task */
      NULL,                 /* Task handle to keep track of created task */
      1);                   /* pin task to core 0 */
}

void loopBox()
{
}