#include <WS2812FX.h>
#include "./utils.h"
#include "../utils.h"
#define RAINBOW_SPEED 100

void rainbowInit(WS2812FX *leds)
{
  setSymmetry(leds, SYM_VERTEX);

  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i);
    seg->speed = RAINBOW_SPEED;
  }
}
void rainbowOnBeat(WS2812FX *leds, double val, double freq)
{
  if(val<5)
    return;
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i);
    WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);
    segrt->counter_mode_step = val;
    seg->speed = seg->speed * 0.9;
  }
}

uint16_t rainbowHandler(WS2812FX *leds)
{
  WS2812FX::Segment *seg = leds->getSegment();
  WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime();
  int seglen = seg->stop - seg->start + 1;
  int halfLength = seglen / 2;

  segrt->counter_mode_step = segrt->counter_mode_step * 0.9;
  if (segrt->counter_mode_step == 0)
  {
    seg->speed = RAINBOW_SPEED;
  }
  for (int i = 0; i < halfLength; i++)
  {
    uint32_t color = 0;
    if (segrt->counter_mode_step > 0)
    {
      double huePercent = 65535.0 * segrt->counter_mode_step / 100.0;
      int hue = huePercent * i / halfLength;
      color = leds->gamma32(leds->ColorHSV(hue));
      color = leds->color_blend(color, seg->colors[0], 100);
    }
    else
    {
      color = leds->getPixelColor(seg->start + i);
      color = leds->color_blend(0, color, 128);
    }
    leds->setPixelColor(seg->start + i, color);
    leds->setPixelColor(seg->start + seglen - 1 - i, color);
  }
  return seg->speed;
}