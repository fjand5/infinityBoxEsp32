#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
#include "../lib/box/soundEff.h"
#include "../lib/box/mic.h"
#include "../lib/box/box.h"

void renderPattern()
{
  renderToggle("Pattern", "pattern_mode", "On/Off", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 if (val == "true")
                 {
                   box.setPatternEffect(true);
                 }
                 if (val == "false")
                 {
                   box.setPatternEffect(false);
                   changeMode(getValue("current_mode", "12").toInt());
                 }
               });
  renderButton("Pattern", "pre_pat_eff_1", "Previous Effect 1", R"({
  })",
               [](String key, String val)
               {
                 box.previousPatternEffect1();
               });
  renderInputText("Pattern", "cur_pat_eff_1", "Current Effect 1", R"({
  })",
                  [](String key, String val)
                  {
                    box.changePaternEffect1(val.toInt());
                  });
  renderButton("Pattern", "nex_pat_eff_1", "Next Effect 1", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.nextPatternEffect1();
               });

  renderButton("Pattern", "pre_pat_eff_2", "Previous Effect 2", R"({
  })",
               [](String key, String val)
               {
                 box.previousPatternEffect2();
               });
  renderInputText("Pattern", "cur_pat_eff_2", "Current Effect 2", R"({
  })",
                  [](String key, String val)
                  {
                    box.changePaternEffect2(val.toInt());
                  });
  renderButton("Pattern", "nex_pat_eff_2", "Next Effect 2", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 box.nextPatternEffect2();
               });
}