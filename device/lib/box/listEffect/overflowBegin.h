#include <WS2812FX.h>
#include "./utils.h"
#define OVER_FLOW_BEGIN_SPEED  50

#define OVER_FLOW_BEGIN_0  0
#define OVER_FLOW_BEGIN_1  1
int overflowMode = OVER_FLOW_BEGIN_0;
void overflowBeginInit(WS2812FX * leds, int mode = OVER_FLOW_BEGIN_0){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = OVER_FLOW_BEGIN_SPEED;
    }
    overflowMode = OVER_FLOW_BEGIN_0;
}
void overflowBeginOnBeat(WS2812FX * leds, double val, double freq){
    if(freq <= 5.0 || val<= 5.0)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);

        if(overflowMode == OVER_FLOW_BEGIN_0)
            if(leds->getPixelColor(seg->stop) == 0){
            seg->speed = 25;
            leds->fade_out(0);
            }else{
                seg->speed = OVER_FLOW_BEGIN_SPEED;
            }
        else
            if(leds->getPixelColor(seg->stop) != 0){
            seg->speed = 25;
            leds->fade_out(0);
            }else{
                seg->speed = OVER_FLOW_BEGIN_SPEED;
            }

        // if(segrt->counter_mode_step != 0){
        //     leds->service();
        // }

        uint32_t color =0;
        int numPixelZero =0;
        // pixel gần pixel đầu tiên có màu hay không

        for(int j = seg->start ; j<= seg->stop; j++){
            if(leds->getPixelColor(j)==0)
                numPixelZero++;
        }

        if(leds->getPixelColor(seg->start) == 0){ // không
            if(numPixelZero<=2)
                color =  seg->colors[1];
            else
                color =  seg->colors[0];
        }else{ // có

            float hsvColor[3];
            color =seg->colors[0];
            rgb2hsv(color, hsvColor);
            hsvColor[0] = (hsvColor[0]+freq/100)/2;
            hsv2rgb(hsvColor[0],hsvColor[1],hsvColor[2], &color);
            uint32_t subColor = leds->getPixelColor(seg->start);
            color = leds->color_blend(subColor, color,  128);
        }
        segrt->counter_mode_step = color;
    }
}

uint16_t overflowBeginHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  int seglen = seg->stop - seg->start + 1;
  int * tmp = new int[seglen - 1];
  for (int i = 0; i < seglen - 1; i++) {
      tmp[i] = leds->getPixelColor(seg->start + i);
  }
  leds->setPixelColor(seg->start, segrt->counter_mode_step);
  for (int i = 1; i < seglen; i++) {
      leds->setPixelColor(seg->start + i, tmp[i - 1]);
  }
  
  segrt->counter_mode_step = 0;
  delete[] tmp;
  return seg->speed; 
}