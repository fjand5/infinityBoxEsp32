#include <WS2812FX.h>

void segmentBeatOnBeat(WS2812FX * leds, double val, double freq){
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

uint16_t segmentBeatHandler(WS2812FX * leds){
  WS2812FX::Segment* seg = leds->getSegment(); // get the current segment
    leds->fade_out(0);
    return seg->speed;
}