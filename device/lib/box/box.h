#pragma once
#include <WS2812FX.h>
#include "ESP32_RMT_Driver.h"
#include "soundEff.h"
#include "../webserver/json/ArduinoJson.h"
#include "../webserver/config.h"
#include "utils.h"

#define RMT_CHANNEL RMT_CHANNEL_0

#define SYM_TEST 0
#define SYM_VERTEX 1
#define SYM_NO_SYM 2
#define SYM_SURFACE 3
// Nhớ thiết lập lại max segment trong thư viện (đã dùng extra_scripts để tự sửa)
#define LED_PIN 23 // digital pin used to drive the LED strip
#define LED_NUM_OF_SEG 24
#define LED_COUNT 288 // number of LEDs on the strip
#define LED_COUNT_ONE_SEG 288 / LED_NUM_OF_SEG
uint16_t musicEffect();
uint16_t patternEffect();

struct CoupleSeg
{
    int first;
    int senconds;
};
int defaulSpeed(int mode)
{
    if (mode == FX_MODE_COLOR_WIPE)
        return 1000;
    if (mode == FX_MODE_COLOR_WIPE_RANDOM)
        return 400;
    if (mode == FX_MODE_SINGLE_DYNAMIC)
        return 50;
    if (mode == FX_MODE_SCAN)
        return 800;
    if (mode == FX_MODE_THEATER_CHASE)
        return 800;
    if (mode == FX_MODE_THEATER_CHASE_RAINBOW)
        return 1000;
    if (mode == FX_MODE_RUNNING_LIGHTS)
        return 1000;
    if (mode == FX_MODE_TWINKLE)
        return 500;
    if (mode == FX_MODE_TWINKLE_RANDOM)
        return 500;
    if (mode == FX_MODE_TWINKLE_FADE)
        return 600;
    if (mode == FX_MODE_TWINKLE_FADE_RANDOM)
        return 600;
    if (mode == FX_MODE_FLASH_SPARKLE)
        return 3000;
    if (mode == FX_MODE_HYPER_SPARKLE)
        return 3000;
    if (mode == FX_MODE_CHASE_RAINBOW)
        return 500;
    if (mode == FX_MODE_CHASE_BLACKOUT)
        return 500;
    if (mode == FX_MODE_FIREWORKS)
        return 1000;
    if (mode == FX_MODE_HALLOWEEN)
        return 500;
    if (mode == FX_MODE_TRICOLOR_CHASE)
        return 500;
    if (mode == FX_MODE_TWINKLEFOX)
        return 1000;
    return 0;
}
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
    if (mode == FX_MODE_MULTI_DYNAMIC)
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
    CoupleSeg coupleSeg[LED_NUM_OF_SEG / 2];
    bool _isConfigMode = false;
    int _mode = 3;
    int _sym = 1;
    int _spd = 500;
    int _bgh = 50;
    uint32_t _timer = 3000;

    bool _isOff = false;
    bool _runTimer = false;

    bool _isReacMusic = false;
    bool _isPatternMode = false;

    uint32_t _colors[3];

    // for test methos
    int _curActiveSegment = 0;

    uint32_t timer = 0;

    // for pattern
    int _pat_eff_1 = 3;
    int _pat_eff_2 = 45;

public:
    Box() : WS2812FX(0, -1, 0, 0, 0){};
    Box(uint16_t num_leds, uint8_t pin, neoPixelType type,
        uint8_t max_num_segments = MAX_NUM_SEGMENTS,
        uint8_t max_num_active_segments = MAX_NUM_ACTIVE_SEGMENTS)
        : WS2812FX(num_leds, pin, type, max_num_segments, max_num_active_segments){

          };
    void settup()
    {
        setSymmetry(this, SYM_VERTEX);
        setCustomMode(musicEffect);

        // setColor(MAX_NUM_SEGMENTS, RED);
        // setCustomMode(patternEffect);
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
        setSymmetry(this, SYM_VERTEX);
        for (int i = 0; i < getNumSegments(); i++)
        {
            setMode(i, _mode);
        }
        setValue("current_mode", String(_mode));
        changeSpeed(getValue(String("speed_mode_") + _mode, String(defaulSpeed(_mode))).toInt(), false);
    }
    void changePaternEffect1(int effect)
    {

        if (!_isPatternMode)
            return;
        while (checkIsIgnoreMode(effect))
        {
            effect++;
        }
        if (effect > 55)
        {
            effect = 0;
            while (checkIsIgnoreMode(effect))
            {
                effect++;
            }
        }
        _pat_eff_1 = effect;
        int _pat_spd_1 = getValue(String("speed_mode_") + _pat_eff_1, String(defaulSpeed(_mode))).toInt();
        int _pat_spd_2= getValue(String("speed_mode_") + _pat_eff_2, String(defaulSpeed(_mode))).toInt();
        setSymmetry(this, SYM_VERTEX, true);
        for (int i = 0; i < getNumSegments() / 2; i++)
        {
            setMode(i, _pat_eff_1);
            setSpeed(i, _pat_spd_1);
        }
        for (int i = getNumSegments() / 2; i < getNumSegments(); i++)
        {
            setMode(i, _pat_eff_2);
            setSpeed(i, _pat_spd_2);
        }
        setValue("cur_pat_eff_1", String(_pat_eff_1));
        changeSpeed(getValue(String("speed_mode_") + _pat_eff_1, String(defaulSpeed(_mode))).toInt(), false);
    }
    int getPatternEffect1()
    {
        return _pat_eff_1;
    }
    int getPatternEffect2()
    {
        return _pat_eff_2;
    }
    void changePaternEffect2(int effect)
    {

        if (!_isPatternMode)
            return;
        while (checkIsIgnoreMode(effect))
        {
            effect++;
        }
        if (effect > 55)
        {
            effect = 0;
            while (checkIsIgnoreMode(effect))
            {
                effect++;
            }
        }
        _pat_eff_2 = effect;
        int _pat_spd_1 = getValue(String("speed_mode_") + _pat_eff_1, String(defaulSpeed(_mode))).toInt();
        int _pat_spd_2= getValue(String("speed_mode_") + _pat_eff_2, String(defaulSpeed(_mode))).toInt();
        setSymmetry(this, SYM_VERTEX, true);
        for (int i = 0; i < getNumSegments() / 2; i++)
        {
            setMode(i, _pat_eff_1);
            setSpeed(i, _pat_spd_1);
        }
        for (int i = getNumSegments() / 2; i < getNumSegments(); i++)
        {
            setMode(i, _pat_eff_2);
            setSpeed(i, _pat_spd_2);
        }
        setValue("cur_pat_eff_2", String(_pat_eff_2));
    }
    void setPatternEffect(bool val)
    {

        _isPatternMode = val;
        if (val)
        {
            offTimer();
            setValue("pattern_mode", "true");

            changePaternEffect1(getValue("cur_pat_eff_1", "3").toInt());
            changePaternEffect2(getValue("cur_pat_eff_2", "45").toInt());
        }
        else
        {
            setValue("pattern_mode", "false");
            changeMode(_mode);
        }
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
    void nextPatternEffect1()
    {
        if (!_isPatternMode)
            return;
        do
        {
            _pat_eff_1++;
        } while (checkIsIgnoreMode(_pat_eff_1));

        if (_pat_eff_1 > 55)
        {
            _pat_eff_1 = 0;
            do
            {
                _pat_eff_1++;
            } while (checkIsIgnoreMode(_pat_eff_1));
        }
        changePaternEffect1(_pat_eff_1);
    }
    void previousPatternEffect1()
    {
        if (!_isPatternMode)
            return;
        do
        {
            _pat_eff_1--;
        } while (checkIsIgnoreMode(_pat_eff_1));

        if (_pat_eff_1 < 0)
        {
            _pat_eff_1 = 55;
            do
            {
                _pat_eff_1--;
            } while (checkIsIgnoreMode(_pat_eff_1));
        }
        changePaternEffect1(_pat_eff_1);
    }

    void nextPatternEffect2()
    {
        if (!_isPatternMode)
            return;
        do
        {
            _pat_eff_2++;
        } while (checkIsIgnoreMode(_pat_eff_2));

        if (_pat_eff_2 > 55)
        {
            _pat_eff_2 = 0;
            do
            {
                _pat_eff_2++;
            } while (checkIsIgnoreMode(_pat_eff_2));
        }
        changePaternEffect2(_pat_eff_2);
    }
    void previousPatternEffect2()
    {
        if (!_isPatternMode)
            return;
        do
        {
            _pat_eff_2--;
        } while (checkIsIgnoreMode(_pat_eff_2));

        if (_pat_eff_2 < 0)
        {
            _pat_eff_2 = 55;
            do
            {
                _pat_eff_2--;
            } while (checkIsIgnoreMode(_pat_eff_2));
        }
        changePaternEffect2(_pat_eff_2);
    }
    void setReacMusic(bool val)
    {
        _isReacMusic = val;
        if (val)
        {
            setValue("react_music", "true");
            for (int i = 0; i < getNumSegments(); i++)
            {
                setMode(i, FX_MODE_CUSTOM);
            }
        }
        else
        {
            setValue("react_music", "false");
            changeMode(_mode);
        }
    }
    void changeSpeed(uint16_t spd, bool save = true)
    {
        uint8_t curMode = getMode();
        _spd = spd;
        if (curMode == FX_MODE_CUSTOM)
            return;
        setValue(String("speed_mode_") + _mode, String(_spd), save);
        setValue("speed_inp", String(_spd), save);
        for (int i = 0; i < getNumSegments(); i++)
        {
            setSpeed(i, _spd);
        }
    }
    void setTimer(uint16_t timer)
    {
        setValue("timer_sld", String(timer));
        _timer = timer * 1000;
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
        setValue("brightness_sld", String(bgh));
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
            if (_isReacMusic)
            {
                soundEffectMode++;
                if (soundEffectMode >= SE_COUNT)
                    soundEffectMode = 0;
                setSoundEffectMode(soundEffectMode, this);
            }
            else
            {

                nextMode();
                setValue("current_mode", String(getMode()));
            }
        }

        // chạy để kích beat
        if (_isReacMusic)
        {
            micValFunc();
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

    bool isConfigMode()
    {
        return _isConfigMode;
    }
    void beginConfigMode()
    {
        _isConfigMode = true;
        resetSegments();
        setSegment();
        setMode(FX_MODE_COLOR_WIPE);
    }
    void currentConfigSegment(int num, bool rev)
    {
        if (!_isConfigMode)
            return;
        resetSegments();
        clear();
        setSegment(0,
                   LED_COUNT_ONE_SEG * num,
                   LED_COUNT_ONE_SEG * (num + 1) - 1,
                   FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, rev);
    }
    void currentConfigFace(String faceName)
    {
        if (!_isConfigMode)
            return;
        resetSegments();
        clear();

        int min_seg = getValue(faceName + "_1").toInt();
        bool min_seg_env = getValue(faceName + "_1_rev") == "true";
        int max_seg = getValue(faceName + "_2").toInt();
        bool max_seg_env = getValue(faceName + "_2_rev") == "true";
        int seg_3 = getValue(faceName + "_3").toInt();
        bool seg_3_env = getValue(faceName + "_3_rev") == "true";
        int seg_4 = getValue(faceName + "_4").toInt();
        bool seg_4_env = getValue(faceName + "_4_rev") == "true";

        setSegment(0,
                   LED_COUNT_ONE_SEG * min_seg,
                   LED_COUNT_ONE_SEG * (min_seg + 1) - 1,
                   FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, min_seg_env);
        setSegment(1,
                   LED_COUNT_ONE_SEG * max_seg,
                   LED_COUNT_ONE_SEG * (max_seg + 1) - 1,
                   FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, max_seg_env);
        setSegment(2,
                   LED_COUNT_ONE_SEG * seg_3,
                   LED_COUNT_ONE_SEG * (seg_3 + 1) - 1,
                   FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, seg_3_env);
        setSegment(3,
                   LED_COUNT_ONE_SEG * seg_4,
                   LED_COUNT_ONE_SEG * (seg_4 + 1) - 1,
                   FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, seg_4_env);
    }
    void endConfigMode()
    {
        if (!_isConfigMode)
            return;
        _isConfigMode = false;
        resetSegments();
        setSymmetry(this, SYM_VERTEX);
        setMode(_mode);
    }
    // CoupleSeg getColumn(int num){
    //     return coupleSeg[num];
    // }
    // private:
};

Box box = Box(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint16_t musicEffect(void)
{
    return soundEffHandle(&box);
}
// void handleEffect(Box *leds, int mode)
// {
//     if (mode == FX_MODE_STATIC)
//     {
//         leds->mode_static();
//     }
//     else if (mode == FX_MODE_BLINK)
//     {
//         leds->mode_blink();

//     }
//     else if (mode == FX_MODE_BREATH)
//     {
//         leds->mode_breath();

//     }
//     else if (mode == FX_MODE_COLOR_WIPE)
//     {
//         leds->mode_color_wipe();

//     }
//     else if (mode == FX_MODE_COLOR_WIPE_INV)
//     {
//         leds->mode_color_wipe_inv();

//     }
//     else if (mode == FX_MODE_COLOR_WIPE_REV)
//     {
//         leds->mode_color_wipe_rev();
//     }
//     else if (mode == FX_MODE_COLOR_WIPE_REV_INV)
//     {
//         leds->mode_color_wipe_rev_inv();
//     }
//     else if (mode == FX_MODE_COLOR_WIPE_RANDOM)
//     {
//         leds->mode_color_wipe_random();
//     }
//     else if (mode == FX_MODE_RANDOM_COLOR)
//     {
//         leds->mode_random_color();
//     }
//     else if (mode == FX_MODE_SINGLE_DYNAMIC)
//     {
//         leds->mode_single_dynamic();
//     }
//     else if (mode == FX_MODE_MULTI_DYNAMIC)
//     {
//         leds->mode_multi_dynamic();
//     }
//     else if (mode == FX_MODE_RAINBOW)
//     {
//         leds->mode_rainbow();
//     }
//     else if (mode == FX_MODE_RAINBOW_CYCLE)
//     {
//         leds->mode_rainbow_cycle();
//     }
//     else if (mode == FX_MODE_SCAN)
//     {
//         leds->mode_scan();
//     }
//     else if (mode == FX_MODE_DUAL_SCAN)
//     {
//         leds->mode_dual_scan();
//     }
//     else if (mode == FX_MODE_FADE)
//     {
//         leds->mode_fade();
//     }
//     else if (mode == FX_MODE_THEATER_CHASE)
//     {
//         leds->mode_theater_chase();
//     }
//     else if (mode == FX_MODE_THEATER_CHASE_RAINBOW)
//     {
//         leds->mode_theater_chase_rainbow();
//     }
//     else if (mode == FX_MODE_RUNNING_LIGHTS)
//     {
//         leds->mode_running_lights();
//     }
//     else if (mode == FX_MODE_TWINKLE)
//     {
//         leds->mode_twinkle();
//     }
//     else if (mode == FX_MODE_TWINKLE_RANDOM)
//     {
//         leds->mode_twinkle_random();
//     }
//     else if (mode == FX_MODE_TWINKLE_FADE)
//     {
//         leds->mode_twinkle_fade();
//     }
//     else if (mode == FX_MODE_TWINKLE_FADE_RANDOM)
//     {
//         leds->mode_twinkle_fade_random();
//     }
//     else if (mode == FX_MODE_SPARKLE)
//     {
//         leds->mode_sparkle();
//     }
//     else if (mode == FX_MODE_FLASH_SPARKLE)
//     {
//         leds->mode_flash_sparkle();
//     }
//     else if (mode == FX_MODE_HYPER_SPARKLE)
//     {
//         leds->mode_hyper_sparkle();
//     }
//     else if (mode == FX_MODE_STROBE)
//     {
//         leds->mode_strobe();
//     }
//     else if (mode == FX_MODE_STROBE_RAINBOW)
//     {
//         leds->mode_strobe_rainbow();
//     }
//     else if (mode == FX_MODE_MULTI_STROBE)
//     {
//         leds->mode_multi_strobe();
//     }
//     else if (mode == FX_MODE_BLINK_RAINBOW)
//     {
//         leds->mode_blink_rainbow();
//     }
//     else if (mode == FX_MODE_CHASE_WHITE)
//     {
//         leds->mode_chase_white();
//     }
//     else if (mode == FX_MODE_CHASE_COLOR)
//     {
//         leds->mode_chase_color();
//     }
//     else if (mode == FX_MODE_CHASE_RANDOM)
//     {
//         leds->mode_chase_random();
//     }
//     else if (mode == FX_MODE_CHASE_RAINBOW)
//     {
//         leds->mode_chase_rainbow();
//     }
//     else if (mode == FX_MODE_CHASE_FLASH)
//     {
//         leds->mode_chase_flash();
//     }
//     else if (mode == FX_MODE_CHASE_FLASH_RANDOM)
//     {
//         leds->mode_chase_flash_random();
//     }
//     else if (mode == FX_MODE_CHASE_RAINBOW_WHITE)
//     {
//         leds->mode_chase_rainbow_white();
//     }
//     else if (mode == FX_MODE_CHASE_BLACKOUT)
//     {
//         leds->mode_chase_blackout();
//     }
//     else if (mode == FX_MODE_CHASE_BLACKOUT_RAINBOW)
//     {
//         leds->mode_chase_blackout_rainbow();
//     }
//     else if (mode == FX_MODE_COLOR_SWEEP_RANDOM)
//     {
//         leds->mode_color_sweep_random();
//     }
//     else if (mode == FX_MODE_RUNNING_COLOR)
//     {
//         leds->mode_running_color();
//     }
//     else if (mode == FX_MODE_RUNNING_RED_BLUE)
//     {
//         leds->mode_running_red_blue();
//     }
//     else if (mode == FX_MODE_RUNNING_RANDOM)
//     {
//         leds->mode_running_random();
//     }
//     else if (mode == FX_MODE_LARSON_SCANNER)
//     {
//         leds->mode_larson_scanner();
//     }
//     else if (mode == FX_MODE_COMET)
//     {
//         leds->mode_comet();
//     }
//     else if (mode == FX_MODE_FIREWORKS)
//     {
//         leds->mode_fireworks();
//     }
//     else if (mode == FX_MODE_FIREWORKS_RANDOM)
//     {
//         leds->mode_fireworks_random();
//     }
//     else if (mode == FX_MODE_MERRY_CHRISTMAS)
//     {
//         leds->mode_merry_christmas();
//     }
//     else if (mode == FX_MODE_FIRE_FLICKER)
//     {
//         leds->mode_fire_flicker();
//     }
//     else if (mode == FX_MODE_FIRE_FLICKER_SOFT)
//     {
//         leds->mode_fire_flicker_soft();
//     }
//     else if (mode == FX_MODE_FIRE_FLICKER_INTENSE)
//     {
//         leds->mode_fire_flicker_intense();
//     }
//     else if (mode == FX_MODE_CIRCUS_COMBUSTUS)
//     {
//         leds->mode_circus_combustus();
//     }
//     else if (mode == FX_MODE_HALLOWEEN)
//     {
//         leds->mode_halloween();
//     }
//     else if (mode == FX_MODE_BICOLOR_CHASE)
//     {
//         leds->mode_bicolor_chase();
//     }
//     else if (mode == FX_MODE_TRICOLOR_CHASE)
//     {
//         leds->mode_tricolor_chase();
//     }
//     else if (mode == FX_MODE_TWINKLEFOX)
//     {
//         leds->mode_twinkleFOX();
//     }
// }
// uint16_t patternEffect(void)
// {
//     WS2812FX::Segment *_seg = box.getSegment(); // get the current segment
//     WS2812FX::Segment_runtime *_segrt = box.getSegmentRuntime();
//     if ((_segrt->counter_mode_call % 2) == 0)
//     {
//         // box.mode_rainbow();
//         int tmp = box.getPatternEffect1();
//         handleEffect(&box,tmp);
//         // box.fireworks(GREEN);

//         return defaulSpeed(tmp)/8;
//     }
//     else if ((_segrt->counter_mode_call % 2) == 1)
//     {
//         box.fireworks(RED);
//         return 50;
//     }
// }
