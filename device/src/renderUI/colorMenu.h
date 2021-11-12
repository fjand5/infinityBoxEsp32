#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
#include "../lib/helper.h"

void renderColorMenu(){

  renderInputText("Color","color1_inp","Set color 1",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue("color1_inp",val);
    box.setColor1(stringToColor(val));
  }); 
  
// color 2
  renderInputText("Color","color2_inp","Set color 2",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue("color2_inp",val);
    box.setColor2(stringToColor(val));
  }); 
  
  // color 3
  renderInputText("Color","color3_inp","Set color 3",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue("color3_inp",val);
    box.setColor3(stringToColor(val));
  }); 
  
}