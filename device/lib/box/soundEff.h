#pragma once
#define SE_OVERFLOW_BEGIN         0
#define SE_OVERFLOW_MID           1
#include <WS2812FX.h>
uint8_t soundEffectMode = SE_OVERFLOW_MID;
void setSoundEffectMode(uint8_t eff){
    soundEffectMode = eff;
}
void addColorBegin(WS2812FX * leds, uint8_t colorPosition){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        if(leds->getPixelColor(seg->start) != 0 )
            leds->service();
        leds->setPixelColor(seg->start,seg->colors[colorPosition]);
    }
}
void addColorMid(WS2812FX * leds, uint8_t colorPosition){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        if(leds->getPixelColor(seg->start + seglen/2) != 0 
        || leds->getPixelColor(seg->start + seglen/2 -1) != 0 )
            leds->service();
        leds->setPixelColor(seg->start + seglen/2,seg->colors[colorPosition]);
        leds->setPixelColor(seg->start + seglen/2 - 1,seg->colors[colorPosition]);
    }
}
uint16_t overflowingEffectBegin(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  if(segrt->counter_mode_call % 2){
    int seglen = seg->stop - seg->start + 1;
    int * tmp = new int[seglen - 1];
    for (int i = 0; i < seglen - 1; i++) {
        tmp[i] = leds->getPixelColor(seg->start + i);
    }
    leds->setPixelColor(seg->start, 0);
    for (int i = 1; i < seglen; i++) {
        leds->setPixelColor(seg->start + i, tmp[i - 1]);
    }
    delete[] tmp;
  }
  return seg->speed/2; // return the delay until the next animation step (in msec)
}
uint16_t overflowingEffectMid(WS2812FX * leds){
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
    // segrt->counter_mode_step++;
    // if(segrt->counter_mode_step == seglen/2)
    //     segrt->counter_mode_step = 0;

  }else{
  }
  return seg->speed/2; // return the delay until the next animation step (in msec)
}

// ===================================================== Handler =====================================================
uint16_t soundEffHandle(WS2812FX * leds){
    if(soundEffectMode == SE_OVERFLOW_BEGIN){
        return overflowingEffectBegin(leds);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        return overflowingEffectMid(leds);
    }
}
void onBeat(WS2812FX * leds, double micVal , double freq){
    if(micVal<20)
        return;
    if(soundEffectMode == SE_OVERFLOW_BEGIN){
        if(freq > 10 && freq<= 40)
            addColorBegin(leds, 0);
        else if(freq > 40 && freq<= 80)
            addColorBegin(leds, 1);
        else 
            addColorBegin(leds, 2);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        if(freq > 10 && freq<= 40)
            addColorMid(leds, 0);
        else if(freq > 40 && freq<= 80)
            addColorMid(leds, 1);
        else 
            addColorMid(leds, 2);

    }
}