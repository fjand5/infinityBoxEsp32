#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
#include "../lib/helper.h"

void renderColorMenu()
{
  renderToggle("Color", "color_timer", "Color Timer", R"({
    "newLine":true
  })",
               [](String key, String val)
               {
                 setValue(key, val);
                 if (val == "false")
                 {
                   box.setColor1(stringToColor(getValue("color1_inp")));
                   box.setColor2(stringToColor(getValue("color2_inp")));
                   box.setColor3(stringToColor(getValue("color3_inp")));
                 }
               });
  renderInputText("Color", "color1_inp", "Set color 1", R"({
    "newLine":true
  })",
                  [](String key, String val)
                  {
                    setValue("color1_inp", val);
                    box.setColor1(stringToColor(val));
                  });

  // color 2
  renderInputText("Color", "color2_inp", "Set color 2", R"({
    "newLine":true
  })",
                  [](String key, String val)
                  {
                    setValue("color2_inp", val);
                    box.setColor2(stringToColor(val));
                  });

  // color 3
  renderInputText("Color", "color3_inp", "Set color 3", R"({
    "newLine":true
  })",
                  [](String key, String val)
                  {
                    setValue("color3_inp", val);
                    box.setColor3(stringToColor(val));
                  });
}