#include <WS2812FX.h>
#include "../utils.h"
#include "./utils.h"

#define SHINES_ON_COUNT_LED_MIN 6
#define SHINES_ON_COUNT_LED_MAX 24

#define SHINES_ON_SPEED 250

#define TRIFADE_BLACK (uint8_t) B10000000 // same as REVERSE macro

void shinesOnInit(WS2812FX *leds)
{

  setSymmetry(leds, SYM_SURFACE);
  leds->clear();
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i);
    // leds->setPixelColor(seg->start, seg->colors[0]);
    seg->speed = SHINES_ON_SPEED;
  }
}

void shinesOnOnBeat(WS2812FX *leds, double val, double freq)
{
  if (val < 5)
    return;
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i); // get the current segment
    WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);
    segrt->counter_mode_step = val * SHINES_ON_COUNT_LED_MAX / 100;
    segrt->counter_mode_step = constrain(segrt->counter_mode_step, SHINES_ON_COUNT_LED_MIN, SHINES_ON_COUNT_LED_MAX);
    val = constrain(val, 0, 50);
    seg->speed = 0;
  }
}

uint16_t shinesOnHandler(WS2812FX *leds)
{

  WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime *_segrt = leds->getSegmentRuntime();
  int midValue = _segrt->counter_mode_step / 2;
  float hsv[3];
  rgb2hsv(_seg->colors[0], hsv);
  // for (int i = 0; i < SHINES_ON_COUNT_LED_MAX - SHINES_ON_COUNT_LED_MIN; i++)
  // {
    // blendRange(leds, _seg->start, _seg->stop, 0);
    clearPixelInSegment(leds, _seg);
  // }

  for (int i = 0; i < _segrt->counter_mode_step; i++)
  {
    uint32_t _color;
    hsv[1] = hsv[1] + (float(midValue - i)) / (float)midValue;
    hsv2rgb(hsv[0], hsv[1], hsv[2], &_color);
    setPixelInSegment(leds, _seg, _segrt->counter_mode_call + i, _color);
  }

  int len = _seg->stop - _seg->start + 1;
  rgb2hsv(_seg->colors[1], hsv);
  for (int i = 0; i < _segrt->counter_mode_step; i++)
  {

    uint32_t _color;
    hsv[1] = hsv[1] + (float(midValue - i)) / (float)midValue;
    hsv2rgb(hsv[0], hsv[1], hsv[2], &_color);

    setPixelInSegment(leds, _seg, _segrt->counter_mode_call + len / 2 + i, _color);
  }
  if (_seg->speed < SHINES_ON_SPEED)
  {
    _seg->speed += SHINES_ON_SPEED / 10;
  }else{
    _segrt->counter_mode_step = SHINES_ON_COUNT_LED_MIN;
  }
  return _seg->speed;
}