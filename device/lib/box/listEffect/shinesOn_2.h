#include <WS2812FX.h>
#include "../utils.h"
#include "./utils.h"

#define SHINES_ON_COUNT_LED_MIN 4.0
#define SHINES_ON_COUNT_LED_MAX 20.0

#define SHINES_ON_SPEED 200
void shinesOnOnBeat2(WS2812FX *leds, double val, double freq);
void shinesOnInit2(WS2812FX *leds)
{

  setSymmetry(leds, SYM_SURFACE);
  leds->clear();
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i);
    seg->speed = SHINES_ON_SPEED;
  }
  shinesOnOnBeat2(leds, 99, 99);
}
// float activateLeds = SHINES_ON_COUNT_LED_MAX;

void shinesOnOnBeat2(WS2812FX *leds, double val, double freq)
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
    if(val > _segrt->counter_mode_step)
    _segrt->counter_mode_step = SHINES_ON_COUNT_LED_MAX;
  }
}

uint16_t shinesOnHandler2(WS2812FX *leds)
{

  WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime *_segrt = leds->getSegmentRuntime();
  uint32_t _len = _seg->stop - _seg->start + 1;
  uint32_t index = _segrt->counter_mode_call;
  float activateLeds = _segrt->counter_mode_step;
  // if(_segrt->counter_mode_step < activateLeds)
  
  // if(millis() - _segrt->counter_mode_step > 200){
    clearPixelInSegment(leds, _seg);
  //   _segrt->counter_mode_step = millis();
  // }
  // blendRange(leds, _seg->start, _seg->stop, 0);
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

  rgb2hsv(_seg->colors[1], hsv);
  for (int i = 0; i < activateLeds; i++)
  {

    uint32_t _color;
    hsv[1] = abs(float(activateLeds - i)) / (float(activateLeds));
    hsv2rgb(hsv[0], hsv[1], hsv[2], &_color);
    setPixelInSegment(leds, _seg, index + _len / 2 + i, _color);
  }
  if (activateLeds > SHINES_ON_COUNT_LED_MIN)
  {
      // _segrt->counter_mode_step--;
    _segrt->counter_mode_step-=activateLeds*10/100;

    return 20;
  }
  else
  {
    // _segrt->counter_mode_step = SHINES_ON_COUNT_LED_MIN;
  }
  return _seg->speed;
}