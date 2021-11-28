#include <WS2812FX.h>
#include "../utils.h"

#define STAR_BEAT_SPEED 10

#define STAR_BEAT_MODE_1 0
#define STAR_BEAT_MODE_2 1
int starBeatMode = STAR_BEAT_MODE_1;
void starBeatInit(WS2812FX *leds, int mode = STAR_BEAT_MODE_1)
{
    setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = STAR_BEAT_SPEED;
    }
    starBeatMode = mode;
}
void starBeatOnBeat(WS2812FX *leds, double val, double freq)
{
    if (val <= 5.0)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        if (starBeatMode == STAR_BEAT_MODE_1)
            for (uint16_t j = 0; j < double(seglen) * val / 1000; j++)
            {
         
                    leds->setPixelColor(seg->start + leds->random16(seglen), seg->colors[leds->random16(3)]);
            }
        else
            for (uint16_t j = 0; j < double(seglen) * val / 1000; j++)
            {
                uint32_t color = leds->ColorHSV(65535.0 * freq / 100);

                leds->setPixelColor(seg->start + leds->random16(seglen), color);
            }
    }
}

uint16_t starBeatHandler(WS2812FX *leds)
{
    WS2812FX::Segment *seg = leds->getSegment(); // get the current segment
    int numPixelZero = 0;
    for (int j = seg->start; j <= seg->stop; j++)
    {
        if (leds->getPixelColor(j) == 0)
            numPixelZero++;
        uint32_t color = leds->getPixelColor(j);
        color = leds->color_blend(color, 0, 32);
        leds->setPixelColor(j, color);
    }
    return seg->speed + numPixelZero;
}