#include <WS2812FX.h>

void overflowBeginOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
        if(leds->getPixelColor(seg->start) != 0 )
            leds->service();
        uint32_t color = seg->colors[1];
        leds->setPixelColor(seg->start, leds->color_blend(segrt->counter_mode_step , color, 128));
        segrt->counter_mode_step = color;
    }
}

uint16_t overflowBeginHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  if(segrt->counter_mode_call % 2){
    int seglen = seg->stop - seg->start + 1;
    int * tmp = new int[seglen - 1];
    for (int i = 0; i < seglen - 1; i++) {
        tmp[i] = leds->getPixelColor(seg->start + i);
    }
    leds->setPixelColor(seg->start, 0);
    // leds->fade_out(0);
    for (int i = 1; i < seglen; i++) {
        leds->setPixelColor(seg->start + i, tmp[i - 1]);
    }
    delete[] tmp;
  }
  return seg->speed/2; 
}