#include <WS2812FX.h>
#include "./utils.h"
#include "../utils.h"

#include "../../webserver/config.h"
#define VU_METTER_COLUMN_SPEED 40
#define VU_METTER_COLUMN_SILENT_VAL 5

bool checkIsColumn(uint16_t seg);
bool needRev(uint16_t seg);
void vuMeterColumnInit(WS2812FX *leds)
{
    setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *_seg = leds->getSegment(i);
        WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);
        segrt->aux_param = checkIsColumn(i);
        segrt->aux_param3 = 0;
        _seg->speed = VU_METTER_COLUMN_SPEED;
        for (int j = _seg->start; j <= _seg->stop; j++)
        {
            leds->setPixelColor(j, 0);
        }
    }
    WS2812FX::Segment *_seg;
    bool isRev;

    _seg = leds->getSegment(6);
    isRev = IS_REVERSE;
    leds->getSegmentRuntime(6)->aux_param3 = ~isRev;

    _seg = leds->getSegment(9);
    isRev = IS_REVERSE;
    leds->getSegmentRuntime(9)->aux_param3 = ~isRev;

    _seg = leds->getSegment(12);
    isRev = IS_REVERSE;
    leds->getSegmentRuntime(12)->aux_param3 = ~isRev;

    _seg = leds->getSegment(13);
    isRev = IS_REVERSE;
    leds->getSegmentRuntime(13)->aux_param3 = ~isRev;

    // _seg = leds->getSegment(7);
    // isRev = IS_REVERSE;
    // leds->getSegmentRuntime(7)->aux_param3=isRev;
}

void vuMeterColumnOnBeat(WS2812FX *leds, double val, double freq)
{

    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *_seg = leds->getSegment(i);
        WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);

        if (segrt->counter_mode_step <= VU_METTER_COLUMN_SILENT_VAL )
        {
            leds->setPixelColor(_seg->start, _seg->colors[0]);
        }
        else
        {
            if (!segrt->aux_param)
            {
                // _seg->speed = VU_METTER_COLUMN_SPEED+ val;
                // continue;
            }
            else
            {
                int seglen = _seg->stop - _seg->start + 1;
                double count = val * seglen / 100.00;
                if (segrt->aux_param3)
                    for (uint16_t i = 0; i < count; i++)
                    {
                        uint32_t color;
                        if (leds->getPixelColor(_seg->stop - i) == 0)
                        {
                            float hsvColor[3];
                            rgb2hsv(color, hsvColor);

                            hsvColor[0] = (hsvColor[0] + freq / 100.00) / 2.00;
                            hsv2rgb(hsvColor[0], hsvColor[1], hsvColor[2], &color);

                            leds->setPixelColor(_seg->stop - i, color);
                        }
                    }
                else
                    for (uint16_t i = 0; i < count; i++)
                    {
                        uint32_t color;
                        if (leds->getPixelColor(_seg->start + i) == 0)
                        {
                            float hsvColor[3];
                            rgb2hsv(color, hsvColor);

                            hsvColor[0] = (hsvColor[0] + freq / 100.00) / 2.00;
                            hsv2rgb(hsvColor[0], hsvColor[1], hsvColor[2], &color);

                            leds->setPixelColor(_seg->start + i, color);
                        }
                    }
            }
        }
        segrt->counter_mode_step = val;
    }
}

uint16_t vuMeterColumnHandler(WS2812FX *leds)
{
    WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
    WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime();

    if (segrt->counter_mode_step <= VU_METTER_COLUMN_SILENT_VAL)
    {
        leds->running(_seg->colors[0], 0);
        return _seg->speed * 2;
    }
    else
    {

        int seglen = _seg->stop - _seg->start + 1;
        int maxPos = 0;
        if (segrt->aux_param3)
        {
            for (int i = seglen - 1; i >= 0; i--)
            {
                if (leds->getPixelColor(_seg->stop - i) != 0)
                {
                    leds->setPixelColor(_seg->stop - i, 0);
                    maxPos = i;
                    break;
                }
            }
            for (int i = 0; i < maxPos; i++)
            {
                uint32_t color = leds->getPixelColor(_seg->stop - i);
                color = leds->color_blend(color, 0, 2);
                leds->setPixelColor(_seg->stop - i, color);
            }
        }
        else
        {
            for (int i = seglen - 1; i >= 0; i--)
            {
                if (leds->getPixelColor(_seg->start + i) != 0)
                {
                    leds->setPixelColor(_seg->start + i, 0);
                    maxPos = i;
                    break;
                }
            }
            for (int i = 0; i < maxPos; i++)
            {
                uint32_t color = leds->getPixelColor(_seg->start + i);
                color = leds->color_blend(color, 0, 2);
                leds->setPixelColor(_seg->start + i, color);
            }
        }

        return _seg->speed;
    }
}
bool checkIsColumn(uint16_t seg)
{
    if ((seg == 0) || (seg == 1) || (seg == 4) || (seg == 5)

        || (seg == 10) || (seg == 11)

        || (seg == 14) || (seg == 15)

        || (seg == 16) || (seg == 17)

        || (seg == 18) || (seg == 19)

        || (seg == 20) || (seg == 21)

        || (seg == 22) || (seg == 23))
        return false;
    else
        return true;
}