#pragma once
#include <WS2812FX.h>
#include "ESP32_RMT_Driver.h"
#include "soundEff.h"
#include "../webserver/json/ArduinoJson.h"
#include "../webserver/config.h"
#define RMT_CHANNEL RMT_CHANNEL_0

// Nhớ thiết lập lại max segment trong thư viện (đã dùng extra_scripts để tự sửa)
#define LED_PIN 23    // digital pin used to drive the LED strip
#define LED_NUM_OF_SEG 24
#define LED_COUNT 288 // number of LEDs on the strip
#define LED_COUNT_ONE_SEG 288/LED_NUM_OF_SEG

#define SYM_TEST 0
#define SYM_VERTEX 1
#define SYM_NO_SYM 2
#define SYM_SURFACE 3
uint16_t musicEffect();
struct CoupleSeg {
    int first;
    int senconds;
};
// int defaulSpeed(int mode){
//     if(mode == )
// }
bool checkIsIgnoreMode(int mode)
{
    // if (mode == FX_MODE_STATIC)
    //     return true;
    if (mode == FX_MODE_BLINK)
        return true;
    if (mode == FX_MODE_COLOR_WIPE_INV)
        return true;
    if (mode == FX_MODE_COLOR_WIPE_REV)
        return true;
    if (mode == FX_MODE_COLOR_WIPE_REV_INV)
        return true;
    if (mode == FX_MODE_RANDOM_COLOR)
        return true;
    if (mode == FX_MODE_RAINBOW_CYCLE)
        return true;
    if (mode == FX_MODE_DUAL_SCAN)
        return true;
    if (mode == FX_MODE_FADE)
        return true;
    if (mode == FX_MODE_SPARKLE)
        return true;
    if (mode == FX_MODE_STROBE)
        return true;
    if (mode == FX_MODE_STROBE_RAINBOW)
        return true;
    if (mode == FX_MODE_MULTI_STROBE)
        return true;
    if (mode == FX_MODE_BLINK_RAINBOW)
        return true;
    if (mode == FX_MODE_CHASE_WHITE)
        return true;
    if (mode == FX_MODE_CHASE_COLOR)
        return true;
    if (mode == FX_MODE_CHASE_RANDOM)
        return true;
    if (mode == FX_MODE_CHASE_FLASH)
        return true;
    if (mode == FX_MODE_CHASE_FLASH_RANDOM)
        return true;
    if (mode == FX_MODE_CHASE_RAINBOW_WHITE)
        return true;
    if (mode == FX_MODE_CHASE_BLACKOUT_RAINBOW)
        return true;
    if (mode == FX_MODE_COLOR_SWEEP_RANDOM)
        return true;
    if (mode == FX_MODE_RUNNING_COLOR)
        return true;
    if (mode == FX_MODE_RUNNING_RED_BLUE)
        return true;
    if (mode == FX_MODE_RUNNING_RANDOM)
        return true;
    if (mode == FX_MODE_LARSON_SCANNER)
        return true;
    if (mode == FX_MODE_COMET)
        return true;
    if (mode == FX_MODE_FIREWORKS_RANDOM)
        return true;
    if (mode == FX_MODE_MERRY_CHRISTMAS)
        return true;
    if (mode == FX_MODE_FIRE_FLICKER)
        return true;
    if (mode == FX_MODE_FIRE_FLICKER_SOFT)
        return true;
    if (mode == FX_MODE_FIRE_FLICKER_INTENSE)
        return true;
    if (mode == FX_MODE_CIRCUS_COMBUSTUS)
        return true;
    if (mode == FX_MODE_BICOLOR_CHASE)
        return true;
    return false;
}
class Box : public WS2812FX
{
private:
    CoupleSeg coupleSeg [LED_NUM_OF_SEG/2];
    bool _isConfigMode = false;
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

    uint32_t timer = 0;

public:
    Box() : WS2812FX(0, -1, 0, 0, 0){};
    Box(uint16_t num_leds, uint8_t pin, neoPixelType type,
        uint8_t max_num_segments = MAX_NUM_SEGMENTS,
        uint8_t max_num_active_segments = MAX_NUM_ACTIVE_SEGMENTS)
        : WS2812FX(num_leds, pin, type, max_num_segments, max_num_active_segments){

          };
    void settup()
    {
        setSymmetry(SYM_VERTEX);
        setCustomMode(musicEffect);
        setBrightness(_bgh);
        init();
        start();
    }
    void changeMode(int mode)
    {

        while (checkIsIgnoreMode(mode))
        {
            mode++;
        }
        if (mode > 55)
        {
            mode = 0;
            while (checkIsIgnoreMode(mode))
            {
                mode++;
            }
        }
        _mode = mode;
        for (int i = 0; i < getNumSegments(); i++)
        {
            setMode(i, _mode);
        }
        changeSpeed(getValue(String("speed_mode_")+_mode).toInt(), false);

    }
    void nextMode()
    {
        do
        {
            _mode++;
        } while (checkIsIgnoreMode(_mode));

        if (_mode > 55)
        {
            _mode = 0;
            do
            {
                _mode++;
            } while (checkIsIgnoreMode(_mode));
        }
        changeMode(_mode);
    }
    void previousMode()
    {
        do
        {
            _mode--;
        } while (checkIsIgnoreMode(_mode));

        if (_mode < 0)
        {
            _mode = 55;
            do
            {
                _mode--;
            } while (checkIsIgnoreMode(_mode));
        }
        changeMode(_mode);
    }
    void setReacMusic(bool val)
    {
        if (val)
        {
            for (int i = 0; i < getNumSegments(); i++)
            {
                setMode(i, FX_MODE_CUSTOM);
            }
        }
        else
        {
            changeMode(_mode);
        }
        _isReacMusic = val;
    }
    void changeSpeed(uint16_t spd, bool save = true)
    {
        uint8_t curMode = getMode();
        _spd = spd;
        if (curMode == FX_MODE_CUSTOM)
            return;
        setValue(String("speed_mode_") + curMode, String(_spd), save);
        setValue("speed_inp", String(_spd), save);
        for (int i = 0; i < getNumSegments(); i++)
        {
            setSpeed(i, _spd);
        }
    }
    void setTimer(uint16_t timer)
    {
        _timer = timer;
    }
    bool isTimerOn()
    {
        return _runTimer;
    }
    void onTimer()
    {
        setValue("timer_tgl", "true");
        _runTimer = true;
    }
    void offTimer()
    {
        setValue("timer_tgl", "false");
        _runTimer = false;
    }
    void changeBrightness(uint16_t bgh, bool gama = false)
    {
        _bgh = map(bgh, 0, 100, 0, 255);
        int val = _bgh;
        if (gama)
            val = gamma8(_bgh);
        setBrightness(val);
    }
    void offBox()
    {
        stop();
        _isOff = true;
    }
    void onBox()
    {
        resume();
        _isOff = false;
    }
    void setColor1(uint32_t color)
    {
        _colors[0] = color;
        for (int i = 0; i < getNumSegments(); i++)
        {
            setColors(i, _colors);
        }
    }
    void setColor2(uint32_t color)
    {
        _colors[1] = color;
        for (int i = 0; i < getNumSegments(); i++)
        {
            setColors(i, _colors);
        }
    }
    void setColor3(uint32_t color)
    {
        _colors[2] = color;
        for (int i = 0; i < getNumSegments(); i++)
        {
            setColors(i, _colors);
        }
    }
    
    void onChangeBeat(double micVal, double freq)
    {
        uint8_t curMode = getMode();

        if (micVal > 100)
            micVal = 100;
        if (micVal < 0)
            micVal = 0;
        if (_isReacMusic && curMode == FX_MODE_CUSTOM)
        {
            onBeat(this, micVal, freq);
        }
    }
    bool beforeService(double (*micValFunc)())
    {
        if (millis() - timer > _timer && _runTimer)
        {
            timer = millis();
            nextMode();
            setValue("current_mode", String(getMode()));
        }

        if (_isReacMusic)
        {
            double micVal = micValFunc();
        }
        return true;
    }
    void affterService()
    {
        if (_isOff)
        {
            strip_off();
        }
    }
    // hepper
    // int getSymmetricNumber(String sym)
    // {
    //     if (sym == "SYM_TEST")
    //         return 0;
    //     if (sym == "SYM_VERTEX")
    //         return 1;
    //     if (sym == "SYM_NO_SYM")
    //         return 2;
    //     if (sym == "SYM_SURFACE")
    //         return 3;
    // }
    // String getSymmetricString(int symNumber)
    // {
    //     if (symNumber == 0)
    //         return "SYM_TEST";
    //     if (symNumber == 1)
    //         return "SYM_VERTEX";
    //     if (symNumber == 2)
    //         return "SYM_NO_SYM";
    //     if (symNumber == 3)
    //         return "SYM_SURFACE";
    // }
    // test method

    void showNextSegment()
    {
        for (int i = 0; i < 24; i++)
        {
            removeActiveSegment(i);
        }
        strip_off();
        _curActiveSegment++;
        _curActiveSegment = _curActiveSegment >= getNumSegments() ? 0 : _curActiveSegment;
        addActiveSegment(_curActiveSegment);
    }
    void showPreviousSegment()
    {
        for (int i = 0; i < 24; i++)
        {
            removeActiveSegment(i);
        }
        strip_off();
        _curActiveSegment--;
        _curActiveSegment = _curActiveSegment < 0 ? getNumSegments() - 1 : _curActiveSegment;
        addActiveSegment(_curActiveSegment);
    }
    int currentSegmentShow()
    {
        return _curActiveSegment;
    }

    bool isConfigMode(){
        return _isConfigMode;
    }
    void beginConfigMode(){
        _isConfigMode = true;
        resetSegments();
        setSegment();
        setMode(FX_MODE_COLOR_WIPE);
    }
    void currentConfigSegment(int num, bool rev){
        if( !_isConfigMode )
            return;
        resetSegments();
        clear();
        setSegment(0,
         LED_COUNT_ONE_SEG * num,
         LED_COUNT_ONE_SEG * (num+1) - 1,
          FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, rev);
    }
    void currentConfigFace(String faceName){
        if( !_isConfigMode )
            return;
        resetSegments();
        clear();

        int seg_1 = getValue(faceName + "_1").toInt();
        bool seg_1_env = getValue(faceName + "_1_rev") == "true";
        int seg_2 = getValue(faceName + "_2").toInt();
        bool seg_2_env = getValue(faceName + "_2_rev") == "true";
        int seg_3 = getValue(faceName + "_3").toInt();
        bool seg_3_env = getValue(faceName + "_3_rev") == "true";
        int seg_4 = getValue(faceName + "_4").toInt();
        bool seg_4_env = getValue(faceName + "_4_rev") == "true";

        setSegment(0,
         LED_COUNT_ONE_SEG * seg_1,
         LED_COUNT_ONE_SEG * (seg_1+1) - 1,
          FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, seg_1_env);
        setSegment(1,
         LED_COUNT_ONE_SEG * seg_2,
         LED_COUNT_ONE_SEG * (seg_2+1) - 1,
          FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, seg_2_env);
        setSegment(2,
         LED_COUNT_ONE_SEG * seg_3,
         LED_COUNT_ONE_SEG * (seg_3+1) - 1,
          FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, seg_3_env);
        setSegment(3,
         LED_COUNT_ONE_SEG * seg_4,
         LED_COUNT_ONE_SEG * (seg_4+1) - 1,
          FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, seg_4_env);
    }
    void endConfigMode(){
        if( !_isConfigMode )
            return;
        _isConfigMode = false;
        resetSegments();
        setSymmetry(SYM_VERTEX);
        setMode(_mode);
    }
    // CoupleSeg getColumn(int num){
    //     return coupleSeg[num];
    // }
    private:
    void setSymmetry(int sym)
    {
        _sym = sym;
        if (sym == SYM_TEST)
        {
            resetSegments();

            setSegment(0, 12 * 0, 12 * 1 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(1, 12 * 1, 12 * 2 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(2, 12 * 2, 12 * 3 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(3, 12 * 3, 12 * 4 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(4, 12 * 4, 12 * 5 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(5, 12 * 5, 12 * 6 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(6, 12 * 6, 12 * 7 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(7, 12 * 7, 12 * 8 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(8, 12 * 8, 12 * 9 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(9, 12 * 9, 12 * 10 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(10, 12 * 10, 12 * 11 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(11, 12 * 11, 12 * 12 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(12, 12 * 12, 12 * 13 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(13, 12 * 13, 12 * 14 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(14, 12 * 14, 12 * 15 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(15, 12 * 15, 12 * 16 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(16, 12 * 16, 12 * 17 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(17, 12 * 17, 12 * 18 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(18, 12 * 18, 12 * 19 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(19, 12 * 19, 12 * 20 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(20, 12 * 20, 12 * 21 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(21, 12 * 21, 12 * 22 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
            setSegment(22, 12 * 22, 12 * 23 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, false);
            setSegment(23, 12 * 23, 12 * 24 - 1, FX_MODE_COLOR_WIPE, _colors, _spd, true);
        }
        else if (sym == SYM_NO_SYM)
        {
            resetSegments();
            setSegment(0, 0, getLength() - 1, _mode, _colors, _spd, false);
        }
        else if (sym == SYM_VERTEX)
        {
            int tmp, index = 0;
            bool isRev = false;
            uint8_t opt;
            resetSegments();
            tmp = getValue("seg_font_1","15").toInt();
            opt = getValue("seg_font_1_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_top_4","16").toInt();
            opt = getValue("seg_top_4_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_font_2","14").toInt();
            opt = getValue("seg_font_2_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_left_2","1").toInt();
            opt = getValue("seg_left_2_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_font_3","13").toInt();
            opt = getValue("seg_font_3_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_bottom_3","9").toInt();
            opt = getValue("seg_bottom_3_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_font_4","12").toInt();
            opt = getValue("seg_font_4_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_right_1","23").toInt();
            opt = getValue("seg_right_1_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_back_1","4").toInt();
            opt = getValue("seg_back_1_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_left_4","3").toInt();
            opt = getValue("seg_left_4_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_back_2","5").toInt();
            opt = getValue("seg_back_2_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_top_2","3").toInt();
            opt = getValue("seg_top_2_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_back_3","6").toInt();
            opt = getValue("seg_back_3_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_right_3","3").toInt();
            opt = getValue("seg_right_3_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_back_4","7").toInt();
            opt = getValue("seg_back_4_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_bottom_1","11").toInt();
            opt = getValue("seg_bottom_1_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_top_3","17").toInt();
            opt = getValue("seg_top_3_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_left_3","2").toInt();
            opt = getValue("seg_left_3_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_top_1","19").toInt();
            opt = getValue("seg_top_1_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_right_4","2").toInt();
            opt = getValue("seg_right_4_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_bottom_4","8").toInt();
            opt = getValue("seg_bottom_4_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_left_1","0").toInt();
            opt = getValue("seg_left_1_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            tmp = getValue("seg_bottom_2","10").toInt();
            opt = getValue("seg_bottom_2_rev","true") == "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp+1) - 1, _mode, _colors, _spd, 
            opt);
            coupleSeg[index/2].first = index;
            index++;
            tmp = getValue("seg_right_2","22").toInt();
            opt = getValue("seg_right_2_rev","true") != "true";
            opt = opt<<7;
            setSegment(index, 12 * tmp, 12 * (tmp + 1) - 1, _mode, _colors, _spd,  
            opt);
            coupleSeg[(index + 1)/2].senconds = index;
            index++;

            
        }
        else if (sym == SYM_SURFACE)
        {
            resetSegments();

            setSegment(0, 0 * getLength() / 6, 1 * getLength() / 6 - 1, _mode, _colors, _spd, false);

            setSegment(1, 1 * getLength() / 6, 2 * getLength() / 6 - 1, _mode, _colors, _spd, false);

            setSegment(2, 2 * getLength() / 6, 3 * getLength() / 6 - 1, _mode, _colors, _spd, false);

            setSegment(3, 3 * getLength() / 6, 4 * getLength() / 6 - 1, _mode, _colors, _spd, false);

            setSegment(4, 4 * getLength() / 6, 5 * getLength() / 6 - 1, _mode, _colors, _spd, false);

            setSegment(5, 5 * getLength() / 6, 6 * getLength() / 6 - 1, _mode, _colors, _spd, false);
        }
        if (_isReacMusic)
            changeMode(FX_MODE_CUSTOM);
        else
            changeMode(_mode);
        // for (int i = 0; i < getNumSegments(); i++){
        //     setMode(i, _mode);
        // }
    }
};

Box box = Box(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint16_t musicEffect(void)
{
    return soundEffHandle(&box);
}