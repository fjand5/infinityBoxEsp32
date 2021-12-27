#include <WS2812FX.h>
#include "../utils.h"

#define OVER_FLOW_MID_SPEED 75
void overflowMidInit(WS2812FX *leds)
{
    setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = OVER_FLOW_MID_SPEED;
    }
}
void overflowMidOnBeat(WS2812FX *leds, double val, double freq)
{
    if (freq <= 5.0 || val <= 5.0)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);

        if (leds->getPixelColor(seg->stop) != 0)
        {
            seg->speed = OVER_FLOW_MID_SPEED / 2;
            blendRange(leds, seg->start, seg->stop, 0, freq * 255 / 100);
        }
        else
        {
            seg->speed = OVER_FLOW_MID_SPEED;
        }

        uint32_t color = 0;
        int numPixelZero = 0;
        for (int j = seg->start; j <= seg->stop; j++)
        {
            if (leds->getPixelColor(j) == 0)
                numPixelZero++;
        }

        if (leds->getPixelColor(seg->start) == 0)
        { // không
            if (numPixelZero <= 4)
                color = seg->colors[1];
            else
                color = seg->colors[0];
        }
        else
        { // có

            float hsvColor[3];
            color = seg->colors[0];
            rgb2hsv(color, hsvColor);
            hsvColor[0] = (hsvColor[0] + freq / 100) / 2;
            hsv2rgb(hsvColor[0], hsvColor[1], hsvColor[2], &color);
            uint32_t subColor = leds->getPixelColor(seg->start);
            color = leds->color_blend(subColor, color, 128);
        }
        segrt->counter_mode_step = color;
    }
}

uint16_t overflowMidHandler(WS2812FX *leds)
{
    WS2812FX::Segment *seg = leds->getSegment(); // get the current segment
    WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime();
    int seglen = seg->stop - seg->start + 1;
    int *tmp = new int[seglen / 2 - 1];

    for (int i = 1; i < seglen / 2; i++)
    {
        tmp[i - 1] = leds->getPixelColor(seg->start + i);
    }

    leds->setPixelColor(seg->start + seglen / 2 - 1, segrt->counter_mode_step);

    for (int i = 0; i < seglen / 2 - 1; i++)
    {
        leds->setPixelColor(seg->start + i, tmp[i]);
    }

    leds->setPixelColor(seg->start + seglen / 2, segrt->counter_mode_step);

    for (int i = seglen / 2 + 1; i < seglen; i++)
    {
        leds->setPixelColor(seg->start + i, tmp[seglen - i - 1]);
    }

    if (seglen % 2 == 1)
    {
        leds->setPixelColor(seg->start + seglen / 2 +1, 0);
    }
    segrt->counter_mode_step = 0;
    delete[] tmp;

    return seg->speed;
}