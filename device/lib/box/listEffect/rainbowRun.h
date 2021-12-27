#include <WS2812FX.h>
#include "./utils.h"
#include "../utils.h"
#define RAINBOW_RUN_SPEED  200

void rainbowRunInit(WS2812FX * leds){
  setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = RAINBOW_RUN_SPEED;
    }
}
void rainbowRunOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
        segrt->counter_mode_step = val;
        seg->speed = seg->speed*0.9;
    }
}


uint16_t rainbowRunHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment();
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  int seglen = seg->stop - seg->start + 1;  
  int midPoint = segrt->counter_mode_call%seglen;
  int halfLength = seglen/2;
  int delta = abs(midPoint - seglen);
  uint32_t * tmp = new uint32_t[seglen];


  // for (int i = 0; i < seglen; i++) {
  //   leds->setPixelColor(seg->start + i, 0);
  // }  
  for (int i = 0; i < seglen/2 ; i++) {		
    uint32_t color = 0;	
    if(segrt->counter_mode_step>0){
      double huePercent = 65535.0*segrt->counter_mode_step/100.0;
      int hue = huePercent*i/halfLength;
      color = leds->gamma32(leds->ColorHSV(hue)); 
    }else{
      color = leds->getPixelColor(seg->start + i);
      color = leds->color_blend(0, color,  200);
    }
    tmp[i] = color;
    tmp[seglen - 1 - i] = color;

  }  

  for (int i = 0; i < seglen; i++) {
    int setPoint = i + delta;
    if(setPoint >= seglen){
      setPoint = setPoint- seglen;
    }
    leds->setPixelColor(seg->start + setPoint, tmp[i]);
  }  
  // for (int i = midPoint; i < midPoint + halfLength; i++) {			
  //   uint32_t color = 0;

  //   int farFromMid = i - midPoint; 
  //   color = leds->color_blend( 0, seg->colors[0], 255*asin(farFromMid)*100/3.14);
  //   // leds->setPixelColor(j, color);
  //   leds->setPixelColor(seg->start + i, color);
  // }
  delete[] tmp;
  segrt->counter_mode_step = segrt->counter_mode_step*0.9;
  if(segrt->counter_mode_step == 0)
    seg->speed = RAINBOW_RUN_SPEED;
  else if(segrt->aux_param3%2) {
    segrt->counter_mode_call--;
  }

  segrt->aux_param3 ++;
  return seg->speed; 
}

// int nextPoint(int curr, int dir, int dist){
//   if(dir == 1){

//   }
// }