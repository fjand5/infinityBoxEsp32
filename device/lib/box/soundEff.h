#pragma once
#define SE_OVERFLOW_BEGIN           0
#define SE_OVERFLOW_MID             1
#define SE_STAR_BEAT                2
#define SE_SEGMENT_BEAT             3
#define SE_VU_METER                 4
#define SE_SHINES_ON                5
#include <WS2812FX.h>
uint8_t soundEffectMode = SE_SHINES_ON;
void setSoundEffectMode(uint8_t eff){
    soundEffectMode = eff;
}
void shinesToFull(WS2812FX * leds, double val){
    if(val < 25)
      return;
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
        int seglen = seg->stop - seg->start + 1;
        double tmp =val*seglen/100;
        segrt->aux_param3 = tmp;
    }
}
void addSegmentRandom(WS2812FX * leds, double val){
    for (uint16_t j = 0; j < val/10; j++){
    WS2812FX::Segment* seg = leds->getSegment(leds->random8(leds->getNumSegments())); // get the current segment
    int seglen = seg->stop - seg->start + 1;
        for (int i = 0; i < seglen;  i++){
            // uint32_t color = leds->Color(leds->random8(),leds->random8(),leds->random8());
            uint32_t color = seg->colors[leds->random8(3)];

            leds->setPixelColor(seg->start + i, color);
        }
    }
}
void addVueMetter(WS2812FX * leds, double val){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        double count = val*seglen/100;
        for (uint16_t i = 0; i < count; i++){
            if(double(i)*100.0/seglen < 33)
                leds->setPixelColor(seg->start + i, seg->colors[0]);
            else if(double(i)*100.0/seglen < 66)
                leds->setPixelColor(seg->start + i, seg->colors[1]);
            else
                leds->setPixelColor(seg->start + i, seg->colors[2]);
        }
    }
}
void addColorRandom(WS2812FX * leds, uint16_t count = 1){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        for (uint16_t j = 0; j < count%3; j++){
            uint32_t color = leds->Color(leds->random8(),leds->random8(),leds->random8());
            leds->setPixelColor(seg->start + leds->random16(seglen), color);
        }
    }
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
uint16_t reduceLeds(WS2812FX * leds){
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
uint16_t fadeAllLeds(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
    leds->fade_out(0);
    return seg->speed;
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
  return seg->speed/2; 
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

  }else{
  }
  return seg->speed/2; 
}
uint16_t patrol(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  int seglen = seg->stop - seg->start + 1;
  uint16_t colorIndex = segrt->aux_param;


  uint32_t counter = segrt->counter_mode_call;    
  uint16_t curPosition = counter  % (seglen);
  if(curPosition == 0){
    segrt->aux_param = leds->random8(3);
  }
  leds->setPixelColor(seg->start + curPosition , seg->colors[colorIndex]);
  int32_t tmp = segrt->aux_param3;
  tmp -= tmp/3;
  tmp = tmp < 0 ? 0: tmp;
  segrt->aux_param3 = tmp;
  if(segrt->aux_param3< seglen*2/3
    && segrt->aux_param3>= 3
  ){
  }else{
    leds->fade_out(0);
  }

  return seg->speed; 
}
// ===================================================== Handler =====================================================
uint16_t soundEffHandle(WS2812FX * leds){
    if(soundEffectMode == SE_OVERFLOW_BEGIN){
        return overflowingEffectBegin(leds);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        return overflowingEffectMid(leds);
    }else if(soundEffectMode == SE_STAR_BEAT || soundEffectMode == SE_SEGMENT_BEAT){
        return fadeAllLeds(leds);
    }else if(soundEffectMode == SE_VU_METER){
        return reduceLeds(leds);
    }else if(soundEffectMode == SE_SHINES_ON){
        return patrol(leds);
    }
}
void onBeat(WS2812FX * leds, double micVal , double freq){
    double noiseVal = 20;
    if(soundEffectMode == SE_STAR_BEAT)
        noiseVal = 10;
    if(micVal<noiseVal)
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

    }else if(soundEffectMode == SE_STAR_BEAT){
        addColorRandom(leds, micVal);
    }else if(soundEffectMode == SE_VU_METER){
        addVueMetter(leds, micVal);
    }else if(soundEffectMode == SE_SEGMENT_BEAT){
        addSegmentRandom(leds, micVal);
    }else if(soundEffectMode == SE_SHINES_ON){
        shinesToFull(leds, micVal);
    }
}