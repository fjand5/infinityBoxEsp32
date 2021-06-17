#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"

uint32_t stringToColor(String val){
    // #ffaabb
    if(!val.startsWith("#")
      || val.length()!=7
    )val = "#ff0000" ;
    uint32_t color;
    String redStr = val.substring(1,3);
    String greenStr = val.substring(3,5);
    String blueStr = val.substring(5);
    int redInt = strtol(redStr.c_str(),NULL,16);
    int greenInt = strtol(greenStr.c_str(),NULL,16);
    int blueInt = strtol(blueStr.c_str(),NULL,16);
    color = box.Color(redInt, greenInt, blueInt);
    return color;

}
void renderColorMenu(){

  renderInputText("Color","color1_inp","Set color 1",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue("color1_inp",val);
    box.setColor1(stringToColor(val));
  }); 
    box.setColor1(stringToColor(getValue("color1_inp")));
  
// color 2
  renderInputText("Color","color2_inp","Set color 2",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue("color2_inp",val);
    box.setColor2(stringToColor(val));
  }); 
    box.setColor2(stringToColor(getValue("color2_inp")));
  
  // color 3
  renderInputText("Color","color3_inp","Set color 3",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue("color3_inp",val);
    box.setColor3(stringToColor(val));
  }); 
    box.setColor3(stringToColor(getValue("color3_inp")));
  
}