#pragma once
#define SE_OVERFLOW_BEGIN           0
#define SE_OVERFLOW_MID             1
#define SE_STAR_BEAT                2
#define SE_SEGMENT_BEAT             3
#define SE_VU_METER                 4
#define SE_SHINES_ON                5
#define SE_RUN_SPEED                6
#define SE_LAZY                     7

#include <WS2812FX.h>
#include "./listEffect/lazy.h"
#include "./listEffect/overflowBegin.h"
#include "./listEffect/overflowMid.h"
#include "./listEffect/starBeat.h"
#include "./listEffect/runSpeed.h"
#include "./listEffect/shinesOn.h"
#include "./listEffect/vuMeter.h"
#include "./listEffect/segmentBeat.h"
uint8_t soundEffectMode = SE_LAZY;
void setSoundEffectMode(uint8_t eff){
    soundEffectMode = eff;
}
// ===================================================== Handler =====================================================
uint16_t soundEffHandle(WS2812FX * leds){
    if(soundEffectMode == SE_OVERFLOW_BEGIN){
        return overflowBeginHandler(leds);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        return overflowMidHandler(leds);
    }else if(soundEffectMode == SE_STAR_BEAT){
        return starBeatHandler(leds);
    }else if(soundEffectMode == SE_SEGMENT_BEAT){
        return segmentBeatHandler(leds);
    }else if(soundEffectMode == SE_VU_METER){
        return vuMeterHandler(leds);
    }else if(soundEffectMode == SE_SHINES_ON){
        return shinesOnHandler(leds);
    }else if(soundEffectMode == SE_RUN_SPEED){
        return runSpeedHandler(leds);
    }else if(soundEffectMode == SE_LAZY){
        return lazyHandler(leds);
    }
}
void onBeat(WS2812FX * leds, double micVal , double freq){
    if(soundEffectMode == SE_OVERFLOW_BEGIN){
        overflowBeginOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        overflowMidOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_STAR_BEAT){
        starBeatOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_VU_METER){
        vuMeterOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_SEGMENT_BEAT){
        segmentBeatOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_SHINES_ON){
        shinesOnOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_RUN_SPEED){
        runSpeedOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_LAZY){
        lazyOnBeat(leds, micVal, freq);
    }
}