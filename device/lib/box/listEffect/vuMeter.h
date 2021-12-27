#include <WS2812FX.h>
#include "./utils.h"
#include "../utils.h"
#define VU_METTER_SPEED 20
#define VU_METTER_SILENT_VAL 5

void vuMeterInit(WS2812FX *leds)
{
    setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = VU_METTER_SPEED;
    }
}

void vuMeterOnBeat(WS2812FX *leds, double val, double freq)
{
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);

        if (val < VU_METTER_SILENT_VAL)
        {
        }
        else
        {
            int seglen = seg->stop - seg->start + 1;
            double count = val * seglen / 100;
            for (uint16_t i = 0; i < count; i++)
            {

                uint32_t color;
                if (leds->getPixelColor(seg->start + i) == 0)
                {
                    float hsvColor[3];
                    rgb2hsv(color, hsvColor);

                    hsvColor[0] = (hsvColor[0] + freq / 100) / 2;
                    hsv2rgb(hsvColor[0], hsvColor[1], hsvColor[2], &color);

                    leds->setPixelColor(seg->start + i, color);
                }
            }
        }
        segrt->aux_param = val;
    }
}

uint16_t vuMeterHandler(WS2812FX *leds)
{
    WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
    WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime();

    int seglen = _seg->stop - _seg->start + 1;
    int maxPos = 0;

    if (segrt->aux_param < VU_METTER_SILENT_VAL)
    {
        leds->running(_seg->colors[0], 0);
        return _seg->speed * 4;
    }
    for (int i = seglen - 1; i >= 0; i--)
    {
        if (leds->getPixelColor(_seg->start + i) != 0 && segrt->aux_param3 != i)
        {
            leds->setPixelColor(_seg->start + i, 0);
            maxPos = i;
            break;
        }
    }
    for (int i = 0; i < maxPos; i++)
    {
        uint32_t color = leds->getPixelColor(_seg->start + i);
        color = leds->color_blend(color, 0, 4);
        leds->setPixelColor(_seg->start + i, color);
    }

    return _seg->speed;
}