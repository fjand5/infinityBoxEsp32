#include <WS2812FX.h>

#include "./utils.h"
#include "../utils.h"
#define RUN_SPEED_SPEED  60
#define RUN_SPEED_SPEED_FAST  30
void runSpeedInit(WS2812FX * leds){
  setSymmetry(leds, SYM_VERTEX);

    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = RUN_SPEED_SPEED;
    }
}


void runSpeedOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = RUN_SPEED_SPEED_FAST;
    }
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
        int seglen = seg->stop - seg->start + 1;
		int hue = (segrt->counter_mode_call%seglen) * (65536L*val/100.0) / seglen;
		uint32_t color = leds->gamma32(leds->ColorHSV(hue)); 
		leds->setPixelColor(seg->start, color);
    }
	leds->service();
	
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        seg->speed = RUN_SPEED_SPEED;
    }
}

uint16_t runSpeedHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment();
	int seglen = seg->stop - seg->start + 1;
	int * tmp = new int[seglen - 1];
	for (int i = 0; i < seglen - 1; i++) {
			tmp[i] = leds->getPixelColor(seg->start + i);
	}
	// leds->setPixelColor(seg->start, 0);
	leds->fade_out(0);
	for (int i = 1; i < seglen; i++) {
			leds->setPixelColor(seg->start + i, tmp[i - 1]);
	}
	delete[] tmp;
  return seg->speed; 
}