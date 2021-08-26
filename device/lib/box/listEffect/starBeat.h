#include <WS2812FX.h>

void starBeatOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        for (uint16_t j = 0; j < 3; j++){
            uint32_t color = leds->ColorHSV((leds->random16()));
            leds->setPixelColor(seg->start + leds->random16(seglen), color);
        }
    }
}

uint16_t starBeatHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
    leds->fade_out(0);
    return seg->speed;
}