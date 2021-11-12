#pragma once
#include "Arduino.h"
#include "box/box.h"
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