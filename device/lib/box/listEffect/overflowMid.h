#include <WS2812FX.h>

void overflowMidOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        if(leds->getPixelColor(seg->start + seglen/2) != 0 
        || leds->getPixelColor(seg->start + seglen/2 -1) != 0 )
            leds->service();
        leds->setPixelColor(seg->start + seglen/2,seg->colors[1]);
        leds->setPixelColor(seg->start + seglen/2 - 1,seg->colors[1]);
    }
}

uint16_t overflowMidHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  if(segrt->counter_mode_call % 2){
    int seglen = seg->stop - seg->start + 1;
    int * tmp = new int[seglen/2 - 1];

    for (int i = 1; i < seglen/2 ; i++) {
        tmp[i-1] = leds->getPixelColor(seg->start + i);
    }

    leds->setPixelColor(seg->start + seglen/2 - 1, 0);

    for (int i = 0; i < seglen/2 - 1 ; i++) {
        leds->setPixelColor(seg->start + i, tmp[i]);
    }
        
    leds->setPixelColor(seg->start + seglen/2, 0);

    for (int i = seglen/2 + 1; i <  seglen; i++) {
        leds->setPixelColor(seg->start + i, tmp[seglen - i - 1]);
    }
    delete[] tmp;

  }else{
  }
  return seg->speed/2; 
}