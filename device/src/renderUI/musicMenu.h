#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
#include "../lib/box/soundEff.h"
void renderMusic(){

  renderToggle("Music","react_music","Music",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue(key,val);
    if(val == "true"){
      onReact();
    }if(val == "false"){
      offReact();
    }
  }); 
  if(getValue("react_music") == "true"){
    onReact();
  }else{
    offReact();
  }

  
  renderButton("Music","music_mode_0","Overflow from center",R"({
  })",
  [](String key, String val){
      setSoundEffectMode(SE_OVERFLOW_BEGIN);
  });   
  
  renderButton("Music","music_mode_1","Overflow from begin",R"({
  })",
  [](String key, String val){
      setSoundEffectMode(SE_OVERFLOW_MID);
  });   

  
}