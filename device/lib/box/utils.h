#pragma once
#include <WS2812FX.h>
#include "../webserver/config.h"
#include "../helper.h"

#define SYM_TEST 0
#define SYM_VERTEX 1
#define SYM_NO_SYM 2
#define SYM_SURFACE 3

void setSymmetry(WS2812FX *leds, int sym)
{
    int mode, color, speed;
    mode = leds->getMode();
    color = leds->getColor();
    speed = leds->getSpeed();

    if (sym == SYM_TEST)
    {
        leds->resetSegments();

        leds->setSegment(0, 12 * 0, 12 * 1 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(1, 12 * 1, 12 * 2 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(2, 12 * 2, 12 * 3 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(3, 12 * 3, 12 * 4 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(4, 12 * 4, 12 * 5 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(5, 12 * 5, 12 * 6 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(6, 12 * 6, 12 * 7 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(7, 12 * 7, 12 * 8 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(8, 12 * 8, 12 * 9 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(9, 12 * 9, 12 * 10 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(10, 12 * 10, 12 * 11 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(11, 12 * 11, 12 * 12 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(12, 12 * 12, 12 * 13 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(13, 12 * 13, 12 * 14 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(14, 12 * 14, 12 * 15 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(15, 12 * 15, 12 * 16 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(16, 12 * 16, 12 * 17 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(17, 12 * 17, 12 * 18 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(18, 12 * 18, 12 * 19 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(19, 12 * 19, 12 * 20 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(20, 12 * 20, 12 * 21 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(21, 12 * 21, 12 * 22 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(22, 12 * 22, 12 * 23 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(23, 12 * 23, 12 * 24 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
    }
    else if (sym == SYM_NO_SYM)
    {
        leds->resetSegments();
        leds->setSegment(0, 0, leds->getLength() - 1, mode, color, speed, false);
    }
    else if (sym == SYM_VERTEX)
    {
        int tmp, index = 0;
        uint8_t opt;
        leds->resetSegments();
        tmp = getValue("seg_font_1", "15").toInt();
        opt = getValue("seg_font_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_top_4", "16").toInt();
        opt = getValue("seg_top_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_font_2", "14").toInt();
        opt = getValue("seg_font_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_2", "1").toInt();
        opt = getValue("seg_left_2_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_font_3", "13").toInt();
        opt = getValue("seg_font_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_bottom_3", "9").toInt();
        opt = getValue("seg_bottom_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_font_4", "12").toInt();
        opt = getValue("seg_font_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_1", "23").toInt();
        opt = getValue("seg_right_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_1", "4").toInt();
        opt = getValue("seg_back_1_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_4", "3").toInt();
        opt = getValue("seg_left_4_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_2", "5").toInt();
        opt = getValue("seg_back_2_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_top_2", "18").toInt();
        opt = getValue("seg_top_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_3", "6").toInt();
        opt = getValue("seg_back_3_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_3", "21").toInt();
        opt = getValue("seg_right_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_4", "7").toInt();
        opt = getValue("seg_back_4_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_bottom_1", "11").toInt();
        opt = getValue("seg_bottom_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_top_3", "17").toInt();
        opt = getValue("seg_top_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_3", "2").toInt();
        opt = getValue("seg_left_3_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_top_1", "19").toInt();
        opt = getValue("seg_top_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_4", "20").toInt();
        opt = getValue("seg_right_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_bottom_4", "8").toInt();
        opt = getValue("seg_bottom_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_1", "0").toInt();
        opt = getValue("seg_left_1_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_bottom_2", "10").toInt();
        opt = getValue("seg_bottom_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_2", "22").toInt();
        opt = getValue("seg_right_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, mode, color, speed,
                         opt);
    }
    else if (sym == SYM_SURFACE)
    {
        int val1, val2, min_seg, max_seg;
        leds->resetSegments();
        // font
        val1 = getValue("seg_font_1").toInt();
        val2 = getValue("seg_font_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(0, min_seg * 12, (max_seg + 1) * 12 - 1, mode, color, speed, false);

        // back
        val1 = getValue("seg_back_1").toInt();
        val2 = getValue("seg_back_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(1, min_seg * 12, (max_seg + 1) * 12 - 1, mode, color, speed, false);

        // top
        val1 = getValue("seg_top_1").toInt();
        val2 = getValue("seg_top_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(2, min_seg * 12, (max_seg + 1) * 12 - 1, mode, color, speed, false);

        // bottom
        val1 = getValue("seg_bottom_1").toInt();
        val2 = getValue("seg_bottom_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(3, min_seg * 12, (max_seg + 1) * 12 - 1, mode, color, speed, false);

        // left
        val1 = getValue("seg_left_1").toInt();
        val2 = getValue("seg_left_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(4, min_seg * 12, (max_seg + 1) * 12 - 1, mode, color, speed, false);

        // right
        val1 = getValue("seg_right_1").toInt();
        val2 = getValue("seg_right_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(5, min_seg * 12, (max_seg + 1) * 12 - 1, mode, color, speed, false);
    }
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->colors[0] = stringToColor(getValue("color1_inp", "#ff0000"));
        seg->colors[1] = stringToColor(getValue("color2_inp", "#00ff00"));
        seg->colors[2] = stringToColor(getValue("color3_inp", "#0000ff"));
    }
}