#include <WS2812FX.h>

void runSpeedOnBeat(WS2812FX * leds, double val, double freq){
    for (int i = 0; i < leds->getNumSegments(); i++){
        WS2812FX::Segment* seg = leds->getSegment(i);
        WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
        int seglen = seg->stop - seg->start + 1;
				double count = val*seglen/1500;
				for (int j = 0; j < count; j++)
				{
					if(leds->getPixelColor(seg->start) != 0 )
							leds->service();
					uint32_t color = seg->colors[leds->random8(3)];
					leds->setPixelColor(seg->start, leds->color_blend(segrt->counter_mode_step , color, 175));
					segrt->counter_mode_step = color;
				}
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