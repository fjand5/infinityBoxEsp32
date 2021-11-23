#pragma once
#define SE_OVERFLOW_BEGIN           0
#define SE_OVERFLOW_BEGIN2          8
#define SE_OVERFLOW_MID             1
#define SE_STAR_BEAT_1              2
#define SE_STAR_BEAT_2              9
#define SE_SEGMENT_BEAT             3
#define SE_VU_METER                 4
#define SE_SHINES_ON_2              5
#define SE_RUN_SPEED                6
#define SE_LAZY                     7
#define SE_RAINBOW                  10
#define SE_RAINBOW_RUN              11
#define SE_VU_METER_COLUMN          12
#define SE_SHINES_ON_1              13

#include <WS2812FX.h>
#include "./listEffect/lazy.h"
#include "./listEffect/overflowBegin.h"
#include "./listEffect/overflowMid.h"
#include "./listEffect/starBeat.h"
#include "./listEffect/runSpeed.h"
#include "./listEffect/shinesOn_2.h"
#include "./listEffect/shinesOn_1.h"
#include "./listEffect/vuMeter.h"
#include "./listEffect/segmentBeat.h"
#include "./listEffect/rainbow.h"
#include "./listEffect/rainbowRun.h"
#include "./listEffect/vuMeterColumn.h"

uint8_t soundEffectMode = SE_SHINES_ON_2;
void setSoundEffectMode(uint8_t eff, WS2812FX * leds){
    soundEffectMode = eff;
    if(soundEffectMode == SE_OVERFLOW_BEGIN){
        overflowBeginInit(leds);
    }else if(soundEffectMode == SE_OVERFLOW_BEGIN2){
        overflowBeginInit(leds, OVER_FLOW_BEGIN_1);
        
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        overflowMidInit(leds);
        
    }else if(soundEffectMode == SE_STAR_BEAT_1){
        starBeatInit(leds, STAR_BEAT_MODE_1);
        
    }else if(soundEffectMode == SE_STAR_BEAT_2){
        starBeatInit(leds, STAR_BEAT_MODE_2);
        
    }else if(soundEffectMode == SE_SEGMENT_BEAT){
        segmentBeatInit(leds);
    }else if(soundEffectMode == SE_VU_METER){
        vuMeterInit(leds);
        
    }else if(soundEffectMode == SE_SHINES_ON_2){
        shinesOnInit2(leds);
    }else if(soundEffectMode == SE_SHINES_ON_1){
        shinesOnInit1(leds);
    }else if(soundEffectMode == SE_RUN_SPEED){
        runSpeedInit(leds);
    }else if(soundEffectMode == SE_LAZY){
        lazyInit(leds);
    }else if(soundEffectMode == SE_RAINBOW){
        rainbowInit(leds);
    }else if(soundEffectMode == SE_RAINBOW_RUN){
        rainbowRunInit(leds);
    }else if(soundEffectMode == SE_VU_METER_COLUMN){
        vuMeterColumnInit(leds);
    }
    setValue("cur_music_mode", String(eff));
}
// ===================================================== Handler =====================================================
uint16_t soundEffHandle(WS2812FX * leds){
    if(soundEffectMode == SE_OVERFLOW_BEGIN || soundEffectMode == SE_OVERFLOW_BEGIN2){
        return overflowBeginHandler(leds);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        return overflowMidHandler(leds);
    }else if(soundEffectMode == SE_STAR_BEAT_1 || soundEffectMode == SE_STAR_BEAT_2){
        return starBeatHandler(leds);
    }else if(soundEffectMode == SE_SEGMENT_BEAT){
        return segmentBeatHandler(leds);
    }else if(soundEffectMode == SE_VU_METER){
        return vuMeterHandler(leds);
    }else if(soundEffectMode == SE_SHINES_ON_2){
        return shinesOnHandler2(leds);
    }else if(soundEffectMode == SE_SHINES_ON_1){
        return shinesOnHandler1(leds);
    }else if(soundEffectMode == SE_RUN_SPEED){
        return runSpeedHandler(leds);
    }else if(soundEffectMode == SE_LAZY){
        return lazyHandler(leds);
    }else if(soundEffectMode == SE_RAINBOW){
        return rainbowHandler(leds);
    }else if(soundEffectMode == SE_RAINBOW_RUN){
        return rainbowRunHandler(leds);
    }else if(soundEffectMode == SE_VU_METER_COLUMN){
        return vuMeterColumnHandler(leds);
    }
}
void onBeat(WS2812FX * leds, double micVal , double freq){
    if(soundEffectMode == SE_OVERFLOW_BEGIN || soundEffectMode == SE_OVERFLOW_BEGIN2){
        overflowBeginOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_OVERFLOW_MID){
        overflowMidOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_STAR_BEAT_1 || soundEffectMode == SE_STAR_BEAT_2){
        starBeatOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_VU_METER){
        vuMeterOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_SEGMENT_BEAT){
        segmentBeatOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_SHINES_ON_2){
        shinesOnOnBeat2(leds, micVal, freq);
    }else if(soundEffectMode == SE_SHINES_ON_1){
        shinesOnOnBeat1(leds, micVal, freq);
    }else if(soundEffectMode == SE_RUN_SPEED){
        runSpeedOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_LAZY){
        lazyOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_RAINBOW){
        rainbowOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_RAINBOW_RUN){
        rainbowRunOnBeat(leds, micVal, freq);
    }else if(soundEffectMode == SE_VU_METER_COLUMN){
        vuMeterColumnOnBeat(leds, micVal, freq);
    }
}