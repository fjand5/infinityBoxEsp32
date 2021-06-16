
#include "Arduino.h"

#include "lib/box/handleBox.h"
#include "lib/webserver/handleWebserver.h"
typedef void (*HandlerSetColor)();
HandlerSetColor setColor1,setColor2,setColor3;
void setup() {
  Serial.begin(115200);
  setupConfig();
  setupMServer();
  setupBox();

  // color 1
  setColor1 = [](){
    uint32_t color;
    uint8_t red = getValue("red_color1_sld").toInt();
    uint8_t green = getValue("green_color1_sld").toInt();
    uint8_t blue = getValue("blue_color1_sld").toInt();
    color = box.Color(red, green, blue);
    box.setColor1(color);
  };
  setColor1();

  renderInputText("Color","color1_inp","Set color 1",R"({
    "newLine":true
  })",
  [](String key, String val){
    // #ffaabb
    if(!val.startsWith("#")
      || val.length()!=7
    )return;
    uint32_t color;
    String redStr = val.substring(1,3);
    String greenStr = val.substring(3,5);
    String blueStr = val.substring(5);
    int redInt = strtol(redStr.c_str(),NULL,16);
    int greenInt = strtol(greenStr.c_str(),NULL,16);
    int blueInt = strtol(blueStr.c_str(),NULL,16);
    setValue("red_color1_sld",String(redInt));
    setValue("green_color1_sld",String(greenInt));
    setValue("blue_color1_sld",String(blueInt));
    color = box.Color(redInt, greenInt, blueInt);
    box.setColor1(color);
  }); 
  renderSlider("Color","red_color1_sld","RED 1",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("red_color1_sld",val);
    setColor1();
  });  



  renderSlider("Color","green_color1_sld","GREEN 1",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("green_color1_sld",val);
    setColor1();
  });
  
  renderSlider("Color","blue_color1_sld","BLUE 1",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("blue_color1_sld",val);
    setColor1();
  });  

// color 2
  renderInputText("Color","color2_inp","Set color 2",R"({
    "newLine":true
  })",
  [](String key, String val){
    // #ffaabb
    if(!val.startsWith("#")
      || val.length()!=7
    )return;
    uint32_t color;
    String redStr = val.substring(1,3);
    String greenStr = val.substring(3,5);
    String blueStr = val.substring(5);
    int redInt = strtol(redStr.c_str(),NULL,16);
    int greenInt = strtol(greenStr.c_str(),NULL,16);
    int blueInt = strtol(blueStr.c_str(),NULL,16);
    setValue("red_color2_sld",String(redInt));
    setValue("green_color2_sld",String(greenInt));
    setValue("blue_color2_sld",String(blueInt));
    color = box.Color(redInt, greenInt, blueInt);
    box.setColor2(color);
  }); 
  setColor2 = [](){
    uint32_t color;
    uint8_t red = getValue("red_color2_sld").toInt();
    uint8_t green = getValue("green_color2_sld").toInt();
    uint8_t blue = getValue("blue_color2_sld").toInt();
    color = box.Color(red, green, blue);
    box.setColor2(color);
  };
  setColor2();
  renderSlider("Color","red_color2_sld","RED 2",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("red_color2_sld",val);
    setColor2();
  });  
  renderSlider("Color","green_color2_sld","GREEN 2",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("green_color2_sld",val);
    setColor2();
  });
  
  renderSlider("Color","blue_color2_sld","BLUE 2",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("blue_color2_sld",val);
    setColor2();
  });  

  // color 3
  renderInputText("Color","color3_inp","Set color 3",R"({
    "newLine":true
  })",
  [](String key, String val){
    // #ffaabb
    if(!val.startsWith("#")
      || val.length()!=7
    )return;
    uint32_t color;
    String redStr = val.substring(1,3);
    String greenStr = val.substring(3,5);
    String blueStr = val.substring(5);
    int redInt = strtol(redStr.c_str(),NULL,16);
    int greenInt = strtol(greenStr.c_str(),NULL,16);
    int blueInt = strtol(blueStr.c_str(),NULL,16);
    setValue("red_color3_sld",String(redInt));
    setValue("green_color3_sld",String(greenInt));
    setValue("blue_color3_sld",String(blueInt));
    color = box.Color(redInt, greenInt, blueInt);
    box.setColor3(color);
  }); 
  setColor3 = [](){
    uint32_t color;
    uint8_t red = getValue("red_color3_sld").toInt();
    uint8_t green = getValue("green_color3_sld").toInt();
    uint8_t blue = getValue("blue_color3_sld").toInt();
    color = box.Color(red, green, blue);
    box.setColor3(color);
  };
  setColor3();
  renderSlider("Color","red_color3_sld","RED 3",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("red_color3_sld",val);
    setColor3();
  });  
  renderSlider("Color","green_color3_sld","GREEN 3",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("green_color3_sld",val);
    setColor3();
  });
  
  renderSlider("Color","blue_color3_sld","BLUE 3",R"({
    "newLine":true,
    "min":0,
    "max":255
  })",
  [](String key, String val){
    setValue("blue_color3_sld",val);
    setColor3();
  });  

  renderInputText("Symmetry","cur_sym","Current Symmetry",R"({
    "newLine":true
  })",
  [](String key, String val){
  }); 

  box.setSymmetry(box.getSymmetricNumber(getValue("cur_sym")));
  renderButton("Symmetry","sym_no_sym_btn","No Symmetry",R"({
    "newLine":true
  })",
  [](String key, String val){
    box.setSymmetry(SYM_NO_SYM);
    setValue("cur_sym", box.getSymmetricString(SYM_NO_SYM));
  }); 

  renderButton("Symmetry","sym_vertex_btn","Vertex",R"({
    "newLine":true
  })",
  [](String key, String val){
    box.setSymmetry(SYM_VERTEX);
    setValue("cur_sym",box.getSymmetricString(SYM_VERTEX));

  }); 
  
  renderButton("Symmetry","sym_surface_btn","Surface",R"({
    "newLine":true
  })",
  [](String key, String val){
    box.setSymmetry(SYM_SURFACE);
    setValue("cur_sym",box.getSymmetricString(SYM_SURFACE));

  }); 
  renderButton("Symmetry","sym_test_btn","Test",R"({
    "newLine":true
  })",
  [](String key, String val){
    box.setSymmetry(SYM_TEST);
    setValue("cur_sym",box.getSymmetricString(SYM_TEST));

  }); 


  renderButton("infinity Box","next_mode","Next Mode",R"({
    "newLine":true
  })",
  [](String key, String val){
    nextMode();
    setValue("current_mode",String(box.getMode()));

  });   
  renderButton("infinity Box","previous_mode","Previous Mode",R"({
    "newLine":true
  })",
  [](String key, String val){
    previousMode();
    setValue("current_mode",String(box.getMode()));
  }); 
  renderToggle("infinity Box","pause_tgl","Pause/Resume",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue(key,val);
    if(val == "true"){
      resumeBox();
    }if(val == "false"){
      pauseBox();
    }
  }); 
  renderToggle("infinity Box","on_off_tgl","On/Off",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue(key,val);
    if(val == "true"){
      onBox();
    }if(val == "false"){
      offBox();
    }
  }); 

  
  renderButton("infinity Box","next_segment","Next Segment",R"({
    "newLine":true
  })",
  [](String key, String val){
    box.showNextSegment();
    setValue("current_segment_show",String(box.currentSegmentShow()));
  });   
  renderButton("infinity Box","previous_segment","Previous Segment",R"({
    "newLine":true
  })",
  [](String key, String val){
    box.showPreviousSegment();
    setValue("current_segment_show",String(box.currentSegmentShow()));
  }); 
  
  
  renderInputText("infinity Box","current_segment_show","Current Mode",R"({
    "newLine":true
  })");

  renderInputText("infinity Box","current_mode","Current Mode",R"({
    "newLine":true
  })");

  renderSlider("infinity Box","speed_sld","tốc độ",R"({
    "newLine":true,
    "min":0,
    "max":100
  })",
  [](String key, String val){
    changeSpeed(val.toInt());
    setValue("speed_sld",val);
  });
  changeSpeed(getValue("speed_sld").toInt());

  renderSlider("infinity Box","timer_sld","thời gian chuyển",R"({
    "newLine":true,
    "min":1,
    "max":60
  })",
  [](String key, String val){
    setTimer(val.toInt()*1000);
    setValue("timer_sld",val);
  });
  setTimer(getValue("timer_sld").toInt()*1000);

  
  renderToggle("infinity Box","timer_tgl","On/Off timer",R"({
    "newLine":true
  })",
  [](String key, String val){
    setValue(key,val);
    if(val == "true"){
      onTimer();
    }if(val == "false"){
      offTimer();
    }
  }); 


  renderSlider("infinity Box","brightness_sld","độ sáng",R"({
    "newLine":true,
    "min":0,
    "max":100
  })",
  [](String key, String val){
    changeBrightness(val.toInt());
    setValue("brightness_sld",val);
  });
  changeSpeed(getValue("brightness_sld").toInt());

  // renderButton("infinity Box","pause_btn","pause","{}",[](String key, String val){
  //   sendCommand(R"({
  //       "sfg": 1
  // })");
  // });
  // renderButton("infinity Box","reactSpeed_btn","react speed","{}",[](String key, String val){
  //   sendCommand(R"({
  //       "sfg": 2
  // })");
  // });
  // renderButton("infinity Box","reactBright_btn","react bright","{}",[](String key, String val){
  //   sendCommand(R"({
  //       "sfg": 3
  // })");
  // });
  // renderButton("infinity Box","reactIntensity_btn","react intensity","{}",[](String key, String val){
  //   sendCommand(R"({
  //       "sfg": 4
  // })");
  // });
  
  // sendCommand(String("{\"speed\":"+getValue("speed_sld")+"}"));

  // renderSlider("infinity Box","brightness_sld","độ sáng","{}",[](String key, String val){
  //   sendCommand(String("{\"brightness\":"+val+"}"));
  //   setValue("brightness_sld",val);
  // });
  // sendCommand(String("{\"brightness\":"+getValue("brightness_sld")+"}"));

  // renderSlider("infinity Box","intensity_sld","cường độ","{}",[](String key, String val){
  //   sendCommand(String("{\"intensity\":"+val+"}"));
  //   setValue("intensity_sld",val);
  // });
  //   sendCommand(String("{\"intensity\":"+getValue("brightness_sld")+"}"));

}

void loop() {
}