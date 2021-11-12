#pragma once
#include "handleBox.h"
Box lastStateBox;
void beginConfig(){
    lastStateBox = box;
    // box.setSymmetry(SYM_NO_SYM);
    // box.setMode(FX_MODE_COLOR_WIPE);
}
void endConfig(){
    box= lastStateBox;
}