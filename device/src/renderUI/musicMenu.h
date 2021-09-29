#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
#include "../lib/box/soundEff.h"
#include "../lib/box/mic.h"
#include "../lib/box/box.h"

void renderMusic()
{
  renderSlider("Music", "micGain_sld", "Gain", R"({
    "newLine":true,
    "min":1,
    "max":10
  })",
               [](String key, String val)
               {
                 setMicGain(val.toDouble());
                 setValue("micGain_sld", val);
               });
  setMicGain(getValue("micGain_sld", "2").toDouble());

  renderSlider("Music", "takeBeat_sld", "Fix Beat", R"({
    "newLine":true,
    "min":0,
    "max":100
  })",
               [](String key, String val)
               {
                 setTakeBeat(val.toDouble());
                 setValue("takeBeat_sld", val);
               });
  setTakeBeat(getValue("takeBeat_sld", "50").toDouble());

  renderToggle("Music", "react_music", "Music", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 if (val == "true")
                 {
                   setSoundEffectMode(getValue("cur_music_mode", "12").toInt(), &box);
                   onReact();
                 }
                 if (val == "false")
                 {
                   offReact();
                   changeMode(getValue("current_mode", "12").toInt());
                   changeSpeed(getValue("speed_sld", "80").toInt());
                 }
               });
  if(!checkKey("react_music")) setValue("react_music", "false");
  if (getValue("react_music", "false") == "true")
  {
    onReact();
  }
  else
  {
    offReact();
  }

  renderInputText("Music", "cur_music_mode", "Current Mode", R"({
  })",
                  [](String key, String val)
                  {
                    setValue("cur_music_mode", val);
                    setSoundEffectMode(val.toInt(), &box);
                  });
  setSoundEffectMode(getValue("cur_music_mode", "1").toInt(), &box);

  renderButton("Music", "music_mode_0", "Overflow from begin", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_OVERFLOW_BEGIN));
                 setSoundEffectMode(SE_OVERFLOW_BEGIN, &box);
               });

  renderButton("Music", "music_mode_1", "Overflow from center", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_OVERFLOW_MID));
                 setSoundEffectMode(SE_OVERFLOW_MID, &box);
               });

  renderButton("Music", "music_mode_2", "Star Beat", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_STAR_BEAT_1));
                 setSoundEffectMode(SE_STAR_BEAT_1, &box);
               });

  renderButton("Music", "music_mode_3", "VU Metter", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_VU_METER));
                 setSoundEffectMode(SE_VU_METER, &box);
               });

  renderButton("Music", "music_mode_4", "Segment beat", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_SEGMENT_BEAT));
                 setSoundEffectMode(SE_SEGMENT_BEAT, &box);
               });
  renderButton("Music", "music_mode_5", "Shines On", R"({
    newLine: True
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_SHINES_ON));
                 setSoundEffectMode(SE_SHINES_ON, &box);
               });
  renderButton("Music", "music_mode_6", "Run Speed", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_RUN_SPEED));
                 setSoundEffectMode(SE_RUN_SPEED, &box);
               });

  renderButton("Music", "music_mode_7", "LAZY", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_LAZY));
                 setSoundEffectMode(SE_LAZY, &box);
               });

  renderButton("Music", "music_mode_8", "Overflow from begin 2", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_OVERFLOW_BEGIN2));
                 setSoundEffectMode(SE_OVERFLOW_BEGIN2, &box);
               });

  renderButton("Music", "music_mode_9", "Star Beat 2", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_STAR_BEAT_2));
                 setSoundEffectMode(SE_STAR_BEAT_2, &box);
               });

  renderButton("Music", "music_mode_10", "RainBow", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_RAINBOW));
                 setSoundEffectMode(SE_RAINBOW, &box);
               });

  renderButton("Music", "music_mode_11", "RainBow Run", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_RAINBOW_RUN));
                 setSoundEffectMode(SE_RAINBOW_RUN, &box);
               });

  renderButton("Music", "music_mode_12", "Vu Metter Column", R"({
  })",
               [](String key, String val)
               {
                 setValue("cur_music_mode", String(SE_VU_METER_COLUMN));
                 setSoundEffectMode(SE_VU_METER_COLUMN, &box);
               });
}