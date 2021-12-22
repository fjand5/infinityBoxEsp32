#pragma once
#include <Arduino.h>
#include <WS2812FX.h>
float mix(float a, float b, float t) { return a + (b - a) * t; }

float step(float e, float x) { return x < e ? 0.0 : 1.0; }

float fract(float x) { return x - int(x); }

// h: 0->1
// s: 0->1
// v: 0->255
void rgb2hsv(uint32_t rgbColor, float *hsv)
{

  float r = float((rgbColor >> 16) & 0xff);
  float g = float((rgbColor >> 8) & 0xff);
  float b = float((rgbColor >> 0) & 0xff);
  float s = float(step(b, g));
  float px = mix(b, g, s);
  float py = mix(g, b, s);
  float pz = mix(-1.0, 0.0, s);
  float pw = mix(0.6666666, -0.3333333, s);
  s = step(px, r);
  float qx = mix(px, r, s);
  float qz = mix(pw, pz, s);
  float qw = mix(r, px, s);
  float d = qx - min(qw, py);
  hsv[0] = abs(qz + (qw - py) / (6.0 * d + 1e-10));
  hsv[1] = d / (qx + 1e-10);
  hsv[2] = qx;
}
void hsv2rgb(float h, float s, float b, uint32_t *rgb)
{
  float r = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  float g = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  float bl = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);

  *rgb = uint32_t(r) << 16 | uint32_t(g) << 8 | uint32_t(bl);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheelColor(WS2812FX *leds, byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return leds->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return leds->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leds->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void blendRange(WS2812FX *leds, int start, int stop, uint32_t color, uint8_t ratio = 128)
{
  for (int i = start; i <= stop; i++)
  {
    uint32_t _color = leds->getPixelColor(i);
    _color = leds->color_blend(_color, color, ratio);
    leds->setPixelColor(i, _color);
  }
}
int countZeroPixel(WS2812FX *leds, int start, int stop)
{
  int ret = 0;
  for (int j = start; j <= stop; j++)
  {
    if (leds->getPixelColor(j) == 0)
    {
      ret++;
    };
  }
  return ret;
}
int setPixelInSegment(WS2812FX *leds, WS2812FX::Segment *_seg, int index, uint32_t color)
{
  int len = _seg->stop - _seg->start + 1;
  index = index % len;
  if (IS_REVERSE)
  {
    leds->setPixelColor(_seg->stop - index, color);
    index  = len - index - 1;
  }
  else
  {
    leds->setPixelColor(_seg->start + index, color);
  }
  return index;
}
void clearPixelInSegment(WS2812FX *leds, WS2812FX::Segment *_seg)
{
  int len = _seg->stop - _seg->start + 1;

  for (int i = 0; i < len; i++)
  {
    leds->setPixelColor(_seg->start + i, 0);
  }
}