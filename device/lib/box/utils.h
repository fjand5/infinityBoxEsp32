#pragma once
#include <WS2812FX.h>
#include "../webserver/config.h"
#include "../helper.h"

#define SYM_TEST 0
#define SYM_VERTEX 1
#define SYM_NO_SYM 2
#define SYM_SURFACE 3
#define LED_COUNT 288
#define LED_NUM_OF_SEG 24
#define LED_COUNT_ONE_SEG LED_COUNT / LED_NUM_OF_SEG
int current_symmetry = SYM_VERTEX;
void setSymmetry(WS2812FX *leds, int sym, bool x2 = false)
{
    int mode, color, speed;
    current_symmetry = sym;
    mode = leds->getMode();
    color = leds->getColor();
    speed = leds->getSpeed();

    if (sym == SYM_TEST)
    {
        leds->updateLength(LED_COUNT);
        leds->resetSegments();
        leds->setSegment(0, LED_COUNT_ONE_SEG * 0, LED_COUNT_ONE_SEG * 1 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(1, LED_COUNT_ONE_SEG * 1, LED_COUNT_ONE_SEG * 2 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(2, LED_COUNT_ONE_SEG * 2, LED_COUNT_ONE_SEG * 3 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(3, LED_COUNT_ONE_SEG * 3, LED_COUNT_ONE_SEG * 4 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(4, LED_COUNT_ONE_SEG * 4, LED_COUNT_ONE_SEG * 5 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(5, LED_COUNT_ONE_SEG * 5, LED_COUNT_ONE_SEG * 6 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(6, LED_COUNT_ONE_SEG * 6, LED_COUNT_ONE_SEG * 7 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(7, LED_COUNT_ONE_SEG * 7, LED_COUNT_ONE_SEG * 8 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(8, LED_COUNT_ONE_SEG * 8, LED_COUNT_ONE_SEG * 9 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(9, LED_COUNT_ONE_SEG * 9, LED_COUNT_ONE_SEG * 10 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(10, LED_COUNT_ONE_SEG * 10, LED_COUNT_ONE_SEG * 11 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(11, LED_COUNT_ONE_SEG * 11, LED_COUNT_ONE_SEG * 12 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(12, LED_COUNT_ONE_SEG * 12, LED_COUNT_ONE_SEG * 13 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(13, LED_COUNT_ONE_SEG * 13, LED_COUNT_ONE_SEG * 14 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(14, LED_COUNT_ONE_SEG * 14, LED_COUNT_ONE_SEG * 15 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(15, LED_COUNT_ONE_SEG * 15, LED_COUNT_ONE_SEG * 16 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(16, LED_COUNT_ONE_SEG * 16, LED_COUNT_ONE_SEG * 17 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(17, LED_COUNT_ONE_SEG * 17, LED_COUNT_ONE_SEG * 18 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(18, LED_COUNT_ONE_SEG * 18, LED_COUNT_ONE_SEG * 19 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(19, LED_COUNT_ONE_SEG * 19, LED_COUNT_ONE_SEG * 20 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(20, LED_COUNT_ONE_SEG * 20, LED_COUNT_ONE_SEG * 21 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(21, LED_COUNT_ONE_SEG * 21, LED_COUNT_ONE_SEG * 22 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
        leds->setSegment(22, LED_COUNT_ONE_SEG * 22, LED_COUNT_ONE_SEG * 23 - 1, FX_MODE_COLOR_WIPE, color, speed, false);
        leds->setSegment(23, LED_COUNT_ONE_SEG * 23, LED_COUNT_ONE_SEG * 24 - 1, FX_MODE_COLOR_WIPE, color, speed, true);
    }
    else if (sym == SYM_NO_SYM)
    {
        leds->updateLength(LED_COUNT);
        leds->resetSegments();
        
        leds->setSegment(0, 0, leds->getLength() - 1, mode, color, speed, false);
    }
    else if (sym == SYM_VERTEX)
    {
        int tmp;
        uint8_t opt, index = 0;
        uint16_t offset =0;
        leds->updateLength(LED_COUNT);
        leds->resetSegments();
        DOUBLE_VERTEX:
        tmp = getValue("seg_font_1", "15").toInt();
        opt = getValue("seg_font_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_top_4", "16").toInt();
        opt = getValue("seg_top_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_font_2", "14").toInt();
        opt = getValue("seg_font_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_2", "1").toInt();
        opt = getValue("seg_left_2_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_font_3", "13").toInt();
        opt = getValue("seg_font_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_bottom_3", "9").toInt();
        opt = getValue("seg_bottom_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_font_4", "12").toInt();
        opt = getValue("seg_font_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_1", "23").toInt();
        opt = getValue("seg_right_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_1", "4").toInt();
        opt = getValue("seg_back_1_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_4", "3").toInt();
        opt = getValue("seg_left_4_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_2", "5").toInt();
        opt = getValue("seg_back_2_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_top_2", "18").toInt();
        opt = getValue("seg_top_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_3", "6").toInt();
        opt = getValue("seg_back_3_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_3", "21").toInt();
        opt = getValue("seg_right_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_back_4", "7").toInt();
        opt = getValue("seg_back_4_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_bottom_1", "11").toInt();
        opt = getValue("seg_bottom_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_top_3", "17").toInt();
        opt = getValue("seg_top_3_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_3", "2").toInt();
        opt = getValue("seg_left_3_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_top_1", "19").toInt();
        opt = getValue("seg_top_1_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_4", "20").toInt();
        opt = getValue("seg_right_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_bottom_4", "8").toInt();
        opt = getValue("seg_bottom_4_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_left_1", "0").toInt();
        opt = getValue("seg_left_1_rev", "false") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;

        tmp = getValue("seg_bottom_2", "10").toInt();
        opt = getValue("seg_bottom_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        index++;
        tmp = getValue("seg_right_2", "22").toInt();
        opt = getValue("seg_right_2_rev", "true") == "true";
        opt = opt << 7;
        leds->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                         opt);
        if(x2){
            x2 = false;
            index++;
            offset = LED_COUNT;
            leds->updateLength(LED_COUNT*2);
            goto DOUBLE_VERTEX;
        }
    }
    else if (sym == SYM_SURFACE)
    {
        int val1, val2, min_seg, max_seg, offset = 0;
        uint8_t index = 0;
        leds->updateLength(LED_COUNT);
        leds->resetSegments();
        DOUBLE_SURFACE:
        // font
        val1 = getValue("seg_font_1").toInt();
        val2 = getValue("seg_font_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(index, min_seg * LED_COUNT_ONE_SEG + offset, (max_seg + 1) * LED_COUNT_ONE_SEG - 1 + offset, mode, color, speed, false);
        index++;

        // back
        val1 = getValue("seg_back_1").toInt();
        val2 = getValue("seg_back_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(index, min_seg * LED_COUNT_ONE_SEG + offset, (max_seg + 1) * LED_COUNT_ONE_SEG - 1 + offset, mode, color, speed, false);
        index++;

        // top
        val1 = getValue("seg_top_1").toInt();
        val2 = getValue("seg_top_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(index, min_seg * LED_COUNT_ONE_SEG + offset, (max_seg + 1) * LED_COUNT_ONE_SEG - 1 + offset, mode, color, speed, false);
        index++;

        // bottom
        val1 = getValue("seg_bottom_1").toInt();
        val2 = getValue("seg_bottom_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(index, min_seg * LED_COUNT_ONE_SEG + offset, (max_seg + 1) * LED_COUNT_ONE_SEG - 1 + offset, mode, color, speed, false);
        index++;

        // left
        val1 = getValue("seg_left_1").toInt();
        val2 = getValue("seg_left_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(index, min_seg * LED_COUNT_ONE_SEG + offset, (max_seg + 1) * LED_COUNT_ONE_SEG - 1 + offset, mode, color, speed, false);
        index++;

        // right
        val1 = getValue("seg_right_1").toInt();
        val2 = getValue("seg_right_4").toInt();
        min_seg = _min(val1, val2);
        max_seg = _max(val1, val2);
        leds->setSegment(index, min_seg * LED_COUNT_ONE_SEG + offset, (max_seg + 1) * LED_COUNT_ONE_SEG - 1 + offset, mode, color, speed, false);
        index++;
        if(x2){
            x2 = false;
            index++;
            offset = LED_COUNT;
            leds->updateLength(LED_COUNT*2);
            goto DOUBLE_SURFACE;
        }
    }
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->colors[0] = stringToColor(getValue("color1_inp", "#ff0000"));
        seg->colors[1] = stringToColor(getValue("color2_inp", "#00ff00"));
        seg->colors[2] = stringToColor(getValue("color3_inp", "#0000ff"));
    }
}