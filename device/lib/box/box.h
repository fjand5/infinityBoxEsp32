#pragma once
#include <WS2812FX.h>
#include "ESP32_RMT_Driver.h"
#include "soundEff.h"
#include "../webserver/json/ArduinoJson.h"
#include "../webserver/config.h"
#include "utils.h"
#include "utils_box.h"

#define RMT_CHANNEL RMT_CHANNEL_0

#define SYM_TEST 0
#define SYM_VERTEX 1
#define SYM_NO_SYM 2
#define SYM_SURFACE 3
// Nhớ thiết lập lại max segment trong thư viện (đã dùng extra_scripts để tự sửa)
#define LED_PIN 23 // digital pin used to drive the LED strip
#define LED_NUM_OF_SEG 24
#define LED_COUNT 288 // sửa 2 chổ (cả file ultis)
#define LED_COUNT_ONE_SEG LED_COUNT / LED_NUM_OF_SEG
#define LED_COUNT_COLORS 15 // number of LEDs on the strip
uint16_t musicEffect();
uint16_t patternEffect();
void vTaskCodeOneTime(void *pvParameters);
struct CoupleSeg
{
    int first;
    int senconds;
};
uint32_t listColors[LED_COUNT_COLORS][3] = {
    {0x0f2557, 0xee7879, 0xf3a51a},
    {0xff6700, 0x191970, 0xe0e722},
    {0x3e090d, 0xc75f5f, 0x89feff},
    {0x800000, 0xf3a51a, 0x8b4513},
    {0x191970, 0x800000, 0xfffafa},
    {0x8b008b, 0x7fff00, 0xff4500},
    {0x4b0082, 0x800000, 0xff69b4},
    {0x8b4513, 0xe0e722, 0x006400},
    {0xff00ff, 0x9932cc, 0xff00a0},
    {0xfe00fe, 0xdefe47, 0x00b3fe},
    {0x65dc98, 0x8d8980, 0x222035},
    {0xff2a6d, 0xd1f7ff, 0x05d9e8},
    {0xfff69f, 0xd0902f, 0xa15501},
    {0xb0acb0, 0x85ebd9, 0x2f404d},
    {0xff577d, 0xffccdc, 0x0a9cf5},
};
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
    volatile bool _runTimer = false;

    volatile bool _isReacMusic = false;
    bool _isPatternMode = false;

    uint32_t _colors[3];

    // for test methos
    int _curActiveSegment = 0;

    uint32_t timer = 0;

    // for pattern
    int _pat_eff_1 = 3;
    int _pat_eff_2 = 45;
    uint8_t *_patternBuffer = NULL;

    TaskHandle_t taskOneTimeHandle;

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

        xTaskCreatePinnedToCore(
            vTaskCodeOneTime,     /* Function that implements the task. */
            "proccessChangeMode", /* Text name for the task. */
            10000,                /* Stack size in words, not bytes. */
            this,                 /* Parameter passed into the task. */
            1,                    /* Priority at which the task is created. */
            &taskOneTimeHandle,
            0); /* Used to pass out the created task's handle. */
    }
    bool isPatternMode()
    {
        return _isPatternMode;
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
        int _pat_spd_2 = getValue(String("speed_mode_") + _pat_eff_2, String(defaulSpeed(_mode))).toInt();
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
        int _pat_spd_2 = getValue(String("speed_mode_") + _pat_eff_2, String(defaulSpeed(_mode))).toInt();
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
    uint8_t *getPatternBuffer()
    {
        return _patternBuffer;
    }
    int getCurrentMode()
    {
        return _mode;
    }
    void setPatternEffect(bool val)
    {

        if (val)
        {
            setSymmetry(this, SYM_VERTEX, true);
            changePaternEffect1(getValue("cur_pat_eff_1", "3").toInt());
            changePaternEffect2(getValue("cur_pat_eff_2", "45").toInt());
            if (_patternBuffer == NULL)
            {
                _patternBuffer = new uint8_t[getNumBytes() / 2 + 1];
            }

            /*
             Nếu không cấp được bộ nhớ cho buffer
             Thì trả lại hiện trạng cũ cho hệ thống
            */
            if (_patternBuffer == NULL)
            {
                _isPatternMode = false;
                setSymmetry(this, SYM_VERTEX, false);
            }
            else
            {
                log_d(ARDUHAL_LOG_COLOR_W "off timer <=====================================================");
                offTimer();
                setValue("pattern_mode", "true");
                _isPatternMode = true;
                setReacMusic(false);
            }
        }
        else
        {
            setValue("pattern_mode", "false");
            changeMode(_mode);
            _isPatternMode = false;
        }
    }
    void nextMode()
    {
        if (_isPatternMode || _isReacMusic)
            return;
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

        log_d("Current Mode: %d", _mode);
    }
    void randomMode()
    {
        if (_isPatternMode)
            return;

        if (_isReacMusic)
        {
            setSoundEffectRandomMode(this);
        }
        else
        {
            uint8_t tmp = 0;
            do
            {
                tmp = random8(55);
            } while (_mode == tmp);
            _mode = tmp;

            changeMode(_mode);
        }

        log_d("Current Mode: %d", _mode);
    }
    void previousMode()
    {
        if (_isPatternMode || _isReacMusic)
            return;
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

        if (val)
        {
            // if (taskOneTimeHandle != NULL)
            // {
            //     vTaskSuspend(taskOneTimeHandle);
            //     vTaskDelete(taskOneTimeHandle);
            // }
            _isReacMusic = true;
            setPatternEffect(false);
            setValue("react_music", "true");

            xTaskCreatePinnedToCore(
                vTaskCodeOneTime,     /* Function that implements the task. */
                "proccessChangeMode", /* Text name for the task. */
                10000,                /* Stack size in words, not bytes. */
                this,                 /* Parameter passed into the task. */
                1,                    /* Priority at which the task is created. */
                &taskOneTimeHandle,
                0); /* Used to pass out the created task's handle. */
        }
        else
        {
            setValue("react_music", "false");
            changeMode(_mode);
            _isReacMusic = false;
        }
    }
    bool getReactMusic()
    {
        return _isReacMusic;
    }
    void changeSpeed(uint16_t spd, bool save = true)
    {
        uint8_t curMode = getMode();
        _spd = spd;
        if (curMode == FX_MODE_CUSTOM)
            return;
        log_d("change speed: %d; save: %d ", spd, save);
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
        log_d("Timer on: %d", _runTimer);
    }
    void offTimer()
    {
        setValue("timer_tgl", "false");
        _runTimer = false;
        log_d("Timer off: %d", _runTimer);
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
        pause();
        // clear();
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
        // if (!_isConfigMode && _isReacMusic && getMode() != FX_MODE_CUSTOM)
        // {
        //     // set lại Mode cho react,
        //     // phòng trường hợp đã bật rồi nhưng timer chưa phát hiện
        //     setSoundEffectMode(soundEffectMode, this);
        //     for (int i = 0; i < getNumSegments(); i++)
        //     {
        //         setMode(i, FX_MODE_CUSTOM);
        //     }
        // }
        if (!_isConfigMode && _runTimer && millis() - timer > _timer)
        {
            timer = millis();
            randomMode();
            // if (_isReacMusic)
            // {
            //     soundEffectMode++;
            //     if (soundEffectMode >= SE_COUNT)
            //         soundEffectMode = 0;
            //     setSoundEffectMode(soundEffectMode, this);
            // }
            // else
            // {
            //     nextMode();
            // }
        }

        // chạy để kích beat
        if (_isReacMusic)
        {
            micValFunc();
        }
        return !_isOff;
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
void vTaskCodeOneTime(void *pvParameters)
{
    Box *_box = (Box *)pvParameters;
    if (getValue("color_timer", "true") == "true")
    {
        uint8_t index = box.random8(LED_COUNT_COLORS);
        for (int i = 0; i < box.getNumSegments(); i++)
        {
            box.setColors(i, listColors[index]);
        }
    }
    if (_box->getReactMusic())
    {

        setSymmetry(_box, SYM_VERTEX, false);
        for (int i = 0; i < _box->getNumSegments(); i++)
        {
            _box->setMode(i, FX_MODE_CUSTOM);
        }
        setSoundEffectRandomMode(_box);
    }
    else
    {
        int _mode = _box->getCurrentMode(); // _box->pause();
        // không lưu current_mode lại đề chuyển hiệu ứng mượt hơn.
        setValue("current_mode", String(_mode), false);
        _box->changeSpeed(getValue(String("speed_mode_") + _mode, String(defaulSpeed(_mode))).toInt(), false);
        // _box->resume();
        if (current_symmetry != SYM_VERTEX)
            setSymmetry(_box, SYM_VERTEX);
        for (int i = 0; i < _box->getNumSegments(); i++)
        {

            _box->setMode(i, _mode);
            _box->setSpeed(i, getValue(String("speed_mode_") + _mode, String(defaulSpeed(_mode))).toInt());
            delay(750 / _box->getNumSegments());
        }
    }

    vTaskDelete(NULL);
}