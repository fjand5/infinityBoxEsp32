#pragma once
#include <WS2812FX.h>
#include "soundEff.h"
// Nhớ thiết lập lại max segment trong thư viện (đã dùng extra_scripts để tự sửa)
#define LED_PIN    23  // digital pin used to drive the LED strip
#define LED_COUNT 288  // number of LEDs on the strip

#define SYM_TEST 0
#define SYM_VERTEX 1
#define SYM_NO_SYM 2
#define SYM_SURFACE 3
uint16_t musicEffect();
class Box: public WS2812FX
{
private:
    int _mode = 3;
    int _sym = 1;
    int _spd = 500;
    int _bgh = 50;
    uint32_t _timer = 3000;

    bool _isOff = false;
    bool _runTimer = false;

    bool _isReacMusic = false;

    uint32_t _colors[3];

    // for test methos
    int _curActiveSegment = 0;
public:
    Box(uint16_t num_leds, uint8_t pin, neoPixelType type,
      uint8_t max_num_segments=MAX_NUM_SEGMENTS,
      uint8_t max_num_active_segments=MAX_NUM_ACTIVE_SEGMENTS)
      :WS2812FX(num_leds,pin,type,max_num_segments,max_num_active_segments){

    };
    void settup(){
        setCustomMode(musicEffect); 
        init();
        setBrightness(_bgh);
        setSymmetry(SYM_VERTEX);
        start();
    }

    void changeMode(int mode){
        _mode = mode;
        _mode = _mode>=getModeCount()?0:_mode;
        _mode = _mode<0?getModeCount():_mode;
        for (int i = 0; i < getNumSegments(); i++){
            setMode(i,_mode);
        }
        changeSpeed(_spd);
    }
    void nextMode(){
        _mode++;
        _mode = _mode>=getModeCount()?0:_mode;
        for (int i = 0; i < getNumSegments(); i++){
            setMode(i,_mode);
        }
    }
    void previousMode(){
        _mode--;
        _mode = _mode<0?getModeCount():_mode;
        for (int i = 0; i < getNumSegments(); i++){
            setMode(i,_mode);
        }
    }
    void setReacMusic(bool val){
        if(val){
            for (int i = 0; i < getNumSegments(); i++){
                setMode(i,FX_MODE_CUSTOM);
            }
        }
        else{
            changeMode(_mode);
        }
        _isReacMusic = val;
    }
    void changeSpeed(uint16_t spd){
        uint8_t curMode = getMode();
        
        if(curMode == FX_MODE_RANDOM_COLOR)
            _spd = map(spd,0,100,250,0);
        else if(curMode == FX_MODE_BREATH)
            _spd = map(spd,0,100,65535,0);
        else if(curMode == FX_MODE_CUSTOM)
            _spd = map(spd,0,100,100,0);
        else if(curMode == FX_MODE_CUSTOM)
            _spd = map(spd,0,100,100,0);
        else
            _spd = map(spd,0,100,5000,0);

        if(curMode == FX_MODE_CUSTOM)
            return;
        for (int i = 0; i < getNumSegments(); i++){
            setSpeed(i,_spd);
        }
    }
    void setTimer(uint16_t timer){
        _timer = timer;
    }
    void onTimer(){
        _runTimer = true;
    }
    void offTimer(){
        _runTimer = false;
    }
    void changeBrightness(uint16_t bgh, bool gama = false){
        _bgh = map(bgh,0,100,0,255);
        int val = _bgh;
        if(gama)
            val = gamma8(_bgh);
        setBrightness(val);
    }
    void offBox(){
        stop();
        _isOff = true;
    }
    void onBox(){
        resume();
        _isOff = false;

    }
    void setColor1(uint32_t color){
        _colors[0] = color;
        for (int i = 0; i < getNumSegments(); i++){
            setColors(i, _colors);
        }
    }
    void setColor2(uint32_t color){
        _colors[1] = color;
        for (int i = 0; i < getNumSegments(); i++){
            setColors(i, _colors);
        }
    }
    void setColor3(uint32_t color){
        _colors[2] = color;
        for (int i = 0; i < getNumSegments(); i++){
            setColors(i, _colors);
        }
    }
    void setSymmetry(int sym){
        _sym = sym;
        if(sym ==SYM_TEST){
            resetSegments();

            setSegment(0, 12*0,12*1-1, FX_MODE_COLOR_WIPE, _colors, _spd, false); 
            setSegment(1, 12*1,12*2-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(2, 12*2,12*3-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(3, 12*3,12*4-1, FX_MODE_COLOR_WIPE, _colors, _spd, false); 
            setSegment(4, 12*4,12*5-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(5, 12*5,12*6-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(6, 12*6,12*7-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(7, 12*7,12*8-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(8, 12*8,12*9-1, FX_MODE_COLOR_WIPE, _colors, _spd, false); 
            setSegment(9, 12*9,12*10-1,FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(10, 12*10,12*11-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(11, 12*11,12*12-1, FX_MODE_COLOR_WIPE, _colors, _spd, false); 
            setSegment(12, 12*12,12*13-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(13, 12*13,12*14-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(14, 12*14,12*15-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(15, 12*15,12*16-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(16, 12*16,12*17-1, FX_MODE_COLOR_WIPE, _colors, _spd, false); 
            setSegment(17, 12*17,12*18-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(18, 12*18,12*19-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(19, 12*19,12*20-1, FX_MODE_COLOR_WIPE, _colors, _spd, false); 
            setSegment(20, 12*20,12*21-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(21, 12*21,12*22-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
            setSegment(22, 12*22,12*23-1, FX_MODE_COLOR_WIPE,  _colors, _spd, false); 
            setSegment(23, 12*23,12*24-1, FX_MODE_COLOR_WIPE, _colors, _spd, true);  
        }else 
        if(sym ==SYM_NO_SYM){
            resetSegments();
            setSegment(0, 0, getLength() - 1, _mode, _colors, _spd, false); 
        }else 
        if(sym == SYM_VERTEX){
            resetSegments();

            setSegment(0, 12*0,12*1-1, _mode, _colors, _spd, false); 
            setSegment(1, 12*8,12*9-1, _mode, _colors, _spd, false); 

            setSegment(2, 12*3,12*4-1, _mode, _colors, _spd, true); 
            setSegment(3, 12*7,12*8-1, _mode, _colors, _spd, true);  

            setSegment(4, 12*11,12*12-1, _mode, _colors, _spd, true); 
            setSegment(5, 12*4,12*5-1, _mode,  _colors, _spd, false); 

            setSegment(6, 12*2,12*3-1, _mode, _colors, _spd, false);  
            setSegment(7, 12*17,12*18-1, _mode,  _colors, _spd, false); 

            setSegment(8, 12*18,12*19-1, _mode, _colors, _spd, true);  
            setSegment(9, 12*5,12*6-1, _mode, _colors, _spd, true);  

            setSegment(10, 12*21,12*22-1, _mode, _colors, _spd, false);  
            setSegment(11, 12*6,12*7-1, _mode,  _colors, _spd, false); 

            setSegment(12, 12*19,12*20-1, _mode, _colors, _spd, false); 
            setSegment(13, 12*20,12*21-1, _mode,  _colors, _spd, true); 

            setSegment(14, 12*12,12*13-1, _mode,  _colors, _spd, true); 
            setSegment(15, 12*23,12*24-1, _mode, _colors, _spd, false);  

            setSegment(16, 12*15,12*16-1, _mode, _colors, _spd, false);  
            setSegment(17, 12*16,12*17-1, _mode, _colors, _spd, true); 

            setSegment(18, 12*10,12*11-1, _mode, _colors, _spd, false);  
            setSegment(19, 12*22,12*23-1, _mode,  _colors, _spd, true); 

            setSegment(20, 12*13,12*14-1, _mode, _colors, _spd, false);  
            setSegment(21, 12*9,12*10-1, _mode,  _colors, _spd, true); 

            setSegment(22, 12*1,12*2-1, _mode,  _colors, _spd, true); 
            setSegment(23, 12*14,12*15-1, _mode,  _colors, _spd, true); 
        }else 
        if(sym ==SYM_SURFACE){
            resetSegments();

            setSegment(0, 0*getLength()/6, 1*getLength()/6 - 1, _mode, _colors, _spd, false); 

            setSegment(1, 1*getLength()/6, 2*getLength()/6 - 1, _mode, _colors, _spd, false); 

            setSegment(2, 2*getLength()/6, 3*getLength()/6 - 1, _mode, _colors, _spd, false); 

            setSegment(3, 3*getLength()/6, 4*getLength()/6 - 1, _mode, _colors, _spd, false); 

            setSegment(4, 4*getLength()/6, 5*getLength()/6 - 1, _mode, _colors, _spd, false); 

            setSegment(5, 5*getLength()/6, 6*getLength()/6 - 1, _mode, _colors, _spd, false); 


        }
        if(_isReacMusic)
            changeMode(FX_MODE_CUSTOM);
        else
            changeMode(_mode);
        // for (int i = 0; i < getNumSegments(); i++){
        //     setMode(i, _mode);
        // }

    }
    void onChangeBeat(double micVal , double freq){
        uint8_t curMode = getMode();

        if(micVal > 100)
            micVal = 100;
        if(micVal < 0)
            micVal = 0;
        if(_isReacMusic && curMode == FX_MODE_CUSTOM){
            onBeat(this,micVal,freq);   
        }
    }
    bool beforeService(double (*micValFunc)()){
        static uint32_t timer = millis();
        if(millis() - timer > _timer
            && _runTimer
        ){
            timer = millis();
            nextMode();
        }

        if(_isReacMusic){
            double micVal = micValFunc();
        }
        return true;
    }    
    void affterService(){
        if(_isOff){
            strip_off();
        }
        
    }
    // hepper
    int getSymmetricNumber(String sym){
        if(sym == "SYM_TEST") return 0;
        if(sym == "SYM_VERTEX") return 1;
        if(sym == "SYM_NO_SYM") return 2;
        if(sym == "SYM_SURFACE") return 3;
    }
    String getSymmetricString(int symNumber){
        if(symNumber == 0) return "SYM_TEST";
        if(symNumber == 1) return "SYM_VERTEX";
        if(symNumber == 2) return "SYM_NO_SYM";
        if(symNumber == 3) return "SYM_SURFACE";
    }
    // test method

    void showNextSegment(){
        for (int i = 0; i < 24; i++){
            removeActiveSegment(i);
        }
        strip_off();
        _curActiveSegment++;
        _curActiveSegment = _curActiveSegment>=getNumSegments()?0:_curActiveSegment;
        addActiveSegment(_curActiveSegment);
    }
    void showPreviousSegment(){
        for (int i = 0; i < 24; i++){
            removeActiveSegment(i);
        }
        strip_off();
        _curActiveSegment--;
        _curActiveSegment = _curActiveSegment<0?getNumSegments()-1:_curActiveSegment;
        addActiveSegment(_curActiveSegment);
    }
    int currentSegmentShow(){
        return _curActiveSegment;
    }
};

Box box = Box(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


uint16_t musicEffect(void) {
  return soundEffHandle(&box);
}