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

  
  renderInputText("Music","cur_music_mode","Current Mode",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",val);
    setSoundEffectMode(val.toInt());
  }); 
    setSoundEffectMode(getValue("cur_music_mode").toInt());
  
  renderButton("Music","music_mode_0","Overflow from begin",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode","0");
      setSoundEffectMode(SE_OVERFLOW_BEGIN);
  });   
  
  renderButton("Music","music_mode_1","Overflow from center",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode","1");
      setSoundEffectMode(SE_OVERFLOW_MID);
  });   
  
  renderButton("Music","music_mode_2","Star Beat",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode","2");
      setSoundEffectMode(SE_STAR_BEAT);
  });   
  
  renderButton("Music","music_mode_3","VU Metter",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode","3");
      setSoundEffectMode(SE_VU_METER);
  });   

  
}