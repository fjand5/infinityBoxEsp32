#include <WS2812FX.h>
#include "./utils.h"
#include "../utils.h"

#define SEGMENT_BEAT_SPEED 50

void segmentBeatInit(WS2812FX *leds)
{
    setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = SEGMENT_BEAT_SPEED;
    }
}

void segmentBeatOnBeat(WS2812FX *leds, double val, double freq)
{
    // for (uint16_t j = 0; j < val/10; j++){
    WS2812FX::Segment *seg = leds->getSegment(leds->random8(leds->getNumSegments())); // get the current segment
    int seglen = seg->stop - seg->start + 1;
    uint32_t priColor = seg->colors[0];
    for (int i = 0; i < seglen; i++)
    {
        byte wheelPos = i * 255 / seglen;
        uint32_t subColor = wheelColor(leds, wheelPos * val / 100);
        leds->setPixelColor(seg->start + i, leds->color_blend(
                                                priColor,
                                                subColor, 128));
    }
    // }
}

uint16_t segmentBeatHandler(WS2812FX *leds)
{
    WS2812FX::Segment *seg = leds->getSegment(); // get the current segment
    int seglen = seg->stop - seg->start + 1;

    for (int i = 0; i < seglen / 2; i++)
    {
        uint32_t color = leds->getPixelColor(seg->start + i);
        color = leds->color_blend(color, 0, 16 * i + 4); // add 2 for anti zero
        leds->setPixelColor(seg->start + i, color);
    }
    if (seglen % 2 == 1)
    {
        leds->setPixelColor(seg->start + seglen / 2 + 1, 0);
    }
    for (int i = 0; i < seglen / 2; i++)
    {
        uint32_t color = leds->getPixelColor(seg->start - i + seglen - 1);
        color = leds->color_blend(color, 0, 16 * i + 4); // add 2 for anti zero
        leds->setPixelColor(seg->start - i + seglen - 1, color);
    }
    return seg->speed;
}