#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
void renderSettingMenu()
{

  renderButton("setting Box", "previous_mode", "Previous Mode", R"({
  })",
               [](String key, String val)
               {
                 previousMode();
                 setValue("current_mode", String(box.getMode()));
                 setValue("timer_tgl", "false");
                 offTimer();
               });
  renderInputText("setting Box", "current_mode", "Current Mode", R"({
  })",
                  [](String key, String val)
                  {
                    changeMode(val.toInt());
                    setValue("current_mode", String(box.getMode()));
                    setValue("timer_tgl", "false");
                    offTimer();
                  });
  renderButton("setting Box", "next_mode", "Next Mode", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 nextMode();
                 setValue("current_mode", String(box.getMode()));
                 setValue("timer_tgl", "false");
                 offTimer();
               });

  renderToggle("setting Box", "pause_tgl", "Pause/Resume", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 if (val == "true")
                 {
                   resumeBox();
                 }
                 if (val == "false")
                 {
                   pauseBox();
                 }
               });
  renderToggle("setting Box", "on_off_tgl", "Off/On", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 if (val == "true")
                 {
                   onBox();
                 }
                 if (val == "false")
                 {
                   offBox();
                 }
               });
  // renderButton("setting Box", "next_segment", "Next Segment", R"({
  //   "newLine":true
  // })",
  //              [](String key, String val)
  //              {
  //                box.showNextSegment();
  //                setValue("current_segment_show", String(box.currentSegmentShow()));
  //              });
  // renderButton("setting Box", "previous_segment", "Previous Segment", R"({
  //   "newLine":true
  // })",
  //              [](String key, String val)
  //              {
  //                box.showPreviousSegment();
  //                setValue("current_segment_show", String(box.currentSegmentShow()));
  //              });

  // renderInputText("setting Box", "current_segment_show", "Current Mode", R"({
  //   "newLine":true
  // })");

  // renderSlider("setting Box", "speed_sld", "tốc độ", R"({
  //   "newLine":true,
  //   "min":0,
  //   "max":65535
  // })",
  //              [](String key, String val)
  //              {
  //                changeSpeed(val.toInt());
  //                setValue("speed_sld", val);
  //                setValue("speed_inp", val);
  //              });
  renderInputText("setting Box", "speed_inp", "tốc độ", R"({
      "newLine":true,
  })",
                  [](String key, String val)
                  {
                    int v = val.toInt();
                    if (v > 65535)
                      v = 65535;
                    if (v < 0)
                      v = 0;
                    changeSpeed(v);
                    setValue("speed_sld", val);
                    setValue("speed_inp", val);
                  });
  renderSlider("setting Box", "timer_sld", "thời gian chuyển", R"({
    "newLine":true,
    "min":1,
    "max":60
  })",
               [](String key, String val)
               {
                 setTimer(val.toInt() * 1000);
                 setValue("timer_sld", val);
               });

  renderToggle("setting Box", "timer_tgl", "Off/On timer", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 if (val == "true")
                 {
                   onTimer();
                 }
                 if (val == "false")
                 {
                   offTimer();
                 }
               });

  renderSlider("setting Box", "brightness_sld", "độ sáng", R"({
    "newLine":true,
    "min":0,
    "max":100
  })",
               [](String key, String val)
               {
                 changeBrightness(val.toInt());
                 setValue("brightness_sld", val);
               });
}