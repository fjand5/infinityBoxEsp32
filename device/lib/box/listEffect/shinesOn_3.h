#include <WS2812FX.h>
#include "../utils.h"
#include "./utils.h"

#define SHINES_ON_COUNT_LED_MIN 3.0
#define SHINES_ON_COUNT_LED_MAX 11.0

#define SHINES_ON_SPEED 75
void shinesOnOnBeat3(WS2812FX *leds, double val, double freq);
void shinesOnInit3(WS2812FX *leds)
{

  setSymmetry(leds, SYM_VERTEX);
  leds->clear();
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i);
    WS2812FX::Segment_runtime *_segrt = leds->getSegmentRuntime(i);
    _segrt->counter_mode_step = 1;
    seg->speed = SHINES_ON_SPEED;
  }
  shinesOnOnBeat3(leds, 99, 99);
}
// float activateLeds = SHINES_ON_COUNT_LED_MAX;

void shinesOnOnBeat3(WS2812FX *leds, double val, double freq)
{
  if (val < 10)
    return;
  // activateLeds = SHINES_ON_COUNT_LED_MAX;
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *_seg = leds->getSegment(i); // get the current segment
    WS2812FX::Segment_runtime *_segrt = leds->getSegmentRuntime(i);
    // activateLeds = constrain(activateLeds, SHINES_ON_COUNT_LED_MIN, SHINES_ON_COUNT_LED_MAX);
    // val  = val*SHINES_ON_COUNT_LED_MAX/100.0;
    if (val > _segrt->counter_mode_step)
      _segrt->counter_mode_step = SHINES_ON_COUNT_LED_MAX;
  }
}

uint16_t shinesOnHandler3(WS2812FX *leds)
{

  WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime *_segrt = leds->getSegmentRuntime();
  uint32_t _len = _seg->stop - _seg->start + 1;
  uint32_t index = _segrt->counter_mode_call;
  float activateLeds = _segrt->counter_mode_step;
  clearPixelInSegment(leds, _seg);
  float hsv[3];
  rgb2hsv(_seg->colors[0], hsv);
  for (int i = 0; i < activateLeds; i++)
  {
    uint32_t _color;
    hsv[1] = abs(float(activateLeds - i)) / (float(activateLeds));
    hsv[2] = 255.00 * abs(float(activateLeds - i)) / (float(activateLeds));

    hsv2rgb(hsv[0], hsv[1], hsv[2], &_color);
    setPixelInSegment(leds, _seg, index + i, _color);
  }
  if (activateLeds > SHINES_ON_COUNT_LED_MIN)
  {
    // _segrt->counter_mode_step--;
    _segrt->counter_mode_step -= activateLeds * 10 / 100;

    return 40;
  }
  else
  {
    // _segrt->counter_mode_step = SHINES_ON_COUNT_LED_MIN;
  }
  return _seg->speed;
}