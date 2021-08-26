#include <WS2812FX.h>

void vuMeterOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        double count = val*seglen/100;
        for (uint16_t i = 0; i < count; i++){
            uint32_t color1;
            uint32_t color2;
            if(double(i)*100.0/seglen < 50){
                color1 = seg->colors[0];
                color2 = seg->colors[1];
            }
            else{
                color1 = seg->colors[1];
                color2 = seg->colors[2];
            }
            leds->setPixelColor( seg->start + i , leds->color_blend(color1, color2, 255.0*i/count));
        }
    }
}

uint16_t vuMeterHandler(WS2812FX * leds){
    WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
    int seglen = seg->stop - seg->start + 1;
    for (int i = seglen - 1; i >=0; i--){
        if(leds->getPixelColor(seg->start + i) != 0 ){
            leds->setPixelColor(seg->start + i, 0);
            return seg->speed;
        }
       
    }
    return seg->speed;
}