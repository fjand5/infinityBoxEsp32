#include "../lib/webserver/render.h"
#include "../lib/webserver/config.h"
#include "../lib/box/handleBox.h"
#include "../lib/box/soundEff.h"

#include "../lib/box/mic.h"
void renderMusic(){
  renderSlider("Music","micGain_sld","Gain",R"({
    "newLine":true,
    "min":1,
    "max":10
  })",
  [](String key, String val){
    setMicGain(val.toDouble());
    setValue("micGain_sld",val);
  });
  setMicGain(getValue("micGain_sld").toDouble());

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
    setValue("cur_music_mode",String(SE_OVERFLOW_BEGIN));
      setSoundEffectMode(SE_OVERFLOW_BEGIN);
  });   
  
  renderButton("Music","music_mode_1","Overflow from center",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_OVERFLOW_MID));
      setSoundEffectMode(SE_OVERFLOW_MID);
  });   
  
  renderButton("Music","music_mode_2","Star Beat",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_STAR_BEAT));
      setSoundEffectMode(SE_STAR_BEAT);
  });   
  
  renderButton("Music","music_mode_3","VU Metter",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_VU_METER));
      setSoundEffectMode(SE_VU_METER);
  });   
  
  renderButton("Music","music_mode_4","Segment beat",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_SEGMENT_BEAT));
      setSoundEffectMode(SE_SEGMENT_BEAT);
  });    
  renderButton("Music","music_mode_5","Shines On",R"({
    newLine: True
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_SHINES_ON));
    setSoundEffectMode(SE_SHINES_ON);
  });    
  renderButton("Music","music_mode_6","Run Speed",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_RUN_SPEED));
    setSoundEffectMode(SE_RUN_SPEED);
  });    
  
  renderButton("Music","music_mode_7","LAZY",R"({
  })",
  [](String key, String val){
    setValue("cur_music_mode",String(SE_LAZY));
    setSoundEffectMode(SE_LAZY);
  });    

  
}