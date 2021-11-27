#include <WS2812FX.h>

int defaulSpeed(int mode)
{
    if (mode == FX_MODE_COLOR_WIPE)
        return 1000;
    if (mode == FX_MODE_COLOR_WIPE_RANDOM)
        return 400;
    if (mode == FX_MODE_SINGLE_DYNAMIC)
        return 50;
    if (mode == FX_MODE_SCAN)
        return 800;
    if (mode == FX_MODE_THEATER_CHASE)
        return 800;
    if (mode == FX_MODE_THEATER_CHASE_RAINBOW)
        return 1000;
    if (mode == FX_MODE_RUNNING_LIGHTS)
        return 1000;
    if (mode == FX_MODE_TWINKLE)
        return 500;
    if (mode == FX_MODE_TWINKLE_RANDOM)
        return 500;
    if (mode == FX_MODE_TWINKLE_FADE)
        return 600;
    if (mode == FX_MODE_TWINKLE_FADE_RANDOM)
        return 600;
    if (mode == FX_MODE_FLASH_SPARKLE)
        return 3000;
    if (mode == FX_MODE_HYPER_SPARKLE)
        return 3000;
    if (mode == FX_MODE_CHASE_RAINBOW)
        return 500;
    if (mode == FX_MODE_CHASE_BLACKOUT)
        return 500;
    if (mode == FX_MODE_FIREWORKS)
        return 1000;
    if (mode == FX_MODE_HALLOWEEN)
        return 500;
    if (mode == FX_MODE_TRICOLOR_CHASE)
        return 500;
    if (mode == FX_MODE_TWINKLEFOX)
        return 1000;
    return 0;
}
bool checkIsIgnoreMode(int mode)
{
    // if (mode == FX_MODE_STATIC)
    //     return true;
    if (mode == FX_MODE_BLINK)
        return true;
    if (mode == FX_MODE_COLOR_WIPE_INV)
        return true;
    if (mode == FX_MODE_COLOR_WIPE_REV)
        return true;
    if (mode == FX_MODE_COLOR_WIPE_REV_INV)
        return true;
    if (mode == FX_MODE_RANDOM_COLOR)
        return true;
    if (mode == FX_MODE_MULTI_DYNAMIC)
        return true;
    if (mode == FX_MODE_RAINBOW_CYCLE)
        return true;
    if (mode == FX_MODE_DUAL_SCAN)
        return true;
    if (mode == FX_MODE_FADE)
        return true;
    if (mode == FX_MODE_SPARKLE)
        return true;
    if (mode == FX_MODE_STROBE)
        return true;
    if (mode == FX_MODE_STROBE_RAINBOW)
        return true;
    if (mode == FX_MODE_MULTI_STROBE)
        return true;
    if (mode == FX_MODE_BLINK_RAINBOW)
        return true;
    if (mode == FX_MODE_CHASE_WHITE)
        return true;
    if (mode == FX_MODE_CHASE_COLOR)
        return true;
    if (mode == FX_MODE_CHASE_RANDOM)
        return true;
    if (mode == FX_MODE_CHASE_FLASH)
        return true;
    if (mode == FX_MODE_CHASE_FLASH_RANDOM)
        return true;
    if (mode == FX_MODE_CHASE_RAINBOW_WHITE)
        return true;
    if (mode == FX_MODE_CHASE_BLACKOUT_RAINBOW)
        return true;
    if (mode == FX_MODE_COLOR_SWEEP_RANDOM)
        return true;
    if (mode == FX_MODE_RUNNING_COLOR)
        return true;
    if (mode == FX_MODE_RUNNING_RED_BLUE)
        return true;
    if (mode == FX_MODE_RUNNING_RANDOM)
        return true;
    if (mode == FX_MODE_LARSON_SCANNER)
        return true;
    if (mode == FX_MODE_COMET)
        return true;
    if (mode == FX_MODE_FIREWORKS_RANDOM)
        return true;
    if (mode == FX_MODE_MERRY_CHRISTMAS)
        return true;
    if (mode == FX_MODE_FIRE_FLICKER)
        return true;
    if (mode == FX_MODE_FIRE_FLICKER_SOFT)
        return true;
    if (mode == FX_MODE_FIRE_FLICKER_INTENSE)
        return true;
    if (mode == FX_MODE_CIRCUS_COMBUSTUS)
        return true;
    if (mode == FX_MODE_BICOLOR_CHASE)
        return true;
    return false;
}
