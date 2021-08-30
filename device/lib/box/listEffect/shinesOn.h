#include <WS2812FX.h>


#define SHINES_ON_SPEED  40

void shinesOnInit(WS2812FX * leds){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = SHINES_ON_SPEED;
    }
}

void shinesOnOnBeat(WS2812FX * leds, double val, double freq){
    // if(val < 25)
    //   return;
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
        int seglen = seg->stop - seg->start + 1;
        double tmp =val*seglen/150;
        segrt->aux_param3 = tmp;
    }
}

uint16_t shinesOnHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime();
  int seglen = seg->stop - seg->start + 1;
  uint16_t colorIndex = segrt->aux_param;

  uint32_t counter = segrt->counter_mode_call;    
  uint16_t curPosition = counter  % (seglen);
  if(curPosition == 0){
    segrt->aux_param = leds->random8(3);
  }
	uint16_t numOfNotOffLed = 0;
	for (int i = 0; i <  seglen; i++) {
		if(leds->getPixelColor(seg->start+i) != 0)
			numOfNotOffLed++;
	}
	double percentOff = numOfNotOffLed/seglen;
  leds->setPixelColor(seg->start + curPosition - 1 , leds->color_blend(seg->colors[colorIndex], leds->ColorHSV(percentOff*65535), 64) );
  int32_t tmp = segrt->aux_param3;
  tmp -= tmp/3;
  tmp = tmp < 0 ? 0: tmp;
  segrt->aux_param3 = tmp;
  if(segrt->aux_param3 >= 3
  ){
  }else{
    leds->fade_out(0);
  }

  return seg->speed; 
}