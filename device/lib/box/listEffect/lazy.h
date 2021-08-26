#include <WS2812FX.h>

void lazyOnBeat(WS2812FX * leds, double val, double freq){
    for (uint16_t j = 0; j < val/10; j++){
			WS2812FX::Segment* seg = leds->getSegment(leds->random8(leds->getNumSegments())); // get the current segment
			int seglen = seg->stop - seg->start + 1;
			uint32_t priColor= seg->colors[leds->random8(3)];
			for (int i = 0; i < seglen;  i++){
					leds->setPixelColor(seg->start + i, leds->color_blend(
						priColor, 
						leds->ColorHSV(val*65535/100)
						, 128));
			}
    }
}

uint16_t lazyHandler(WS2812FX * leds){
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