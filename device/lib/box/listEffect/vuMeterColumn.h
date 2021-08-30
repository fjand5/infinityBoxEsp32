#include <WS2812FX.h>
#include "./utils.h"
#define VU_METTER_COLUMN_SPEED  40
bool checkIsColumn(uint16_t seg);
void vuMeterColumnInit(WS2812FX * leds){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = VU_METTER_COLUMN_SPEED;
        seg->options = checkIsColumn(i);
        for (int j = seg->start; j <=seg->stop; j++){
            leds->setPixelColor(j, 0);
        }


    }
}

void vuMeterColumnOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        if(!seg->options)
            continue;
        int seglen = seg->stop - seg->start + 1;
        double count = val*seglen/100;
        for (uint16_t i = 0; i < count; i++){
            uint32_t color;
            if(leds->getPixelColor( seg->start + i) == 0){
                float hsvColor[3];
                rgb2hsv(color, hsvColor);

                hsvColor[0] = (hsvColor[0]+freq/100)/2;
                hsv2rgb(hsvColor[0],hsvColor[1],hsvColor[2], &color);

                leds->setPixelColor( seg->start + i , color);
            }
        }
    }
}

uint16_t vuMeterColumnHandler(WS2812FX * leds){
    WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
    if(!seg->options)
        return 0;

    int seglen = seg->stop - seg->start + 1;
    int maxPos = 0;
    for (int i = seglen - 1; i >=0; i--){
        if(leds->getPixelColor(seg->start + i) != 0 ){
            leds->setPixelColor(seg->start + i, 0);
            maxPos = i;
            break;
        }
       
    }
    for (int i = 0; i < maxPos; i++){
        uint32_t color = leds->getPixelColor(seg->start + i);
        color = leds->color_blend(color, 0, 2);
        leds->setPixelColor(seg->start +i, color);
       
    }
    
    return seg->speed;
}
bool checkIsColumn(uint16_t seg){
    if(seg == 2
    || seg == 5
    || seg == 10
    || seg == 11
    || seg == 14
    || seg == 15
    || seg == 22
    || seg == 23
    )
        return true;
    else
        return false;
}