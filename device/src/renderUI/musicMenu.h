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
    "max":100
  })",
               [](String key, String val)
               {
                 setMicGain(val.toDouble());
               });

  renderSlider("Music", "takeBeat_sld", "Fix Beat", R"({
    "newLine":true,
    "min":0,
    "max":100
  })",
               [](String key, String val)
               {
                 setTakeBeat(val.toDouble());
               });

  renderToggle("Music", "react_music", "Music", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 if (val == "true")
                 {
                   onReact();
                   //  setSoundEffectMode(getValue("cur_music_mode", String(SE_STAR_BEAT_1)).toInt(), &box);
                 }
                 if (val == "false")
                 {
                   offReact();
                   changeMode(getValue("current_mode", "12").toInt());
                   //  changeSpeed(getValue("speed_sld", "80").toInt());
                 }
               });

  renderInputText("Music", "cur_music_mode", "Current Mode", R"({
  })",
                  [](String key, String val)
                  {
                    if (box.getReactMusic())
                      setSoundEffectMode(val.toInt(), &box);
                  });

  renderButton("Music", "music_mode_0", "Light Years Ahead", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_OVERFLOW_BEGIN, &box);
               });

  renderButton("Music", "music_mode_1", "Elliptical Circuit", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_OVERFLOW_MID, &box);
               });

  renderButton("Music", "music_mode_2", "The Magnetars", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_STAR_BEAT_1, &box);
               });

  renderButton("Music", "music_mode_3", "Flyby Voyagers", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_VU_METER, &box);
               });

  renderButton("Music", "music_mode_4", "Halo of Stars", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_SEGMENT_BEAT, &box);
               });
  renderButton("Music", "music_mode_5", "Stellar Remnants", R"({
    newLine: True
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_SHINES_ON_2, &box);
               });
  renderButton("Music", "music_mode_6", "The Satellite Set", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_RUN_SPEED, &box);
               });

  // renderButton("Music", "music_mode_7", "LAZY", R"({
  // })",
  //              [](String key, String val)
  //              {
  //                if (box.getReactMusic())
  //                  setSoundEffectMode(SE_LAZY, &box);
  //              });

  renderButton("Music", "music_mode_8", "Marvelous Martians", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_OVERFLOW_BEGIN2, &box);
               });

  renderButton("Music", "music_mode_9", "Exploding Stars", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_STAR_BEAT_2, &box);
               });

  renderButton("Music", "music_mode_10", "The Lava Planets", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_RAINBOW, &box);
               });

  renderButton("Music", "music_mode_11", "Mars Attacks", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_RAINBOW_RUN, &box);
               });

  renderButton("Music", "music_mode_12", "The Dark Energy Stars", R"({
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_VU_METER_COLUMN, &box);
               });
  renderButton("Music", "music_mode_13", "Cosmic Rays", R"({
    newLine: True
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_SHINES_ON_1, &box);
               });
  renderButton("Music", "music_mode_14", "The Omega Nebula", R"({
    newLine: True
  })",
               [](String key, String val)
               {
                 if (box.getReactMusic())
                   setSoundEffectMode(SE_SHINES_ON_3, &box);
               });
}