Import("env")

# access to global construction environment
WS2812FX_PATH = env['PROJECT_LIBDEPS_DIR'] + "\\" +  "\\node32s\WS2812FX\\src\\WS2812FX.h"
f = open(WS2812FX_PATH, "r")
lines = f.readlines()
f.close()

for i, line in enumerate(lines):
    if(line.startswith("#define MAX_NUM_SEGMENTS")):
        lines[i] = "#define MAX_NUM_SEGMENTS \t 24\n"
    if(line.startswith("#define MAX_NUM_ACTIVE_SEGMENTS")):
        lines[i] = "#define MAX_NUM_ACTIVE_SEGMENTS \t 24\n"
f = open(WS2812FX_PATH, "w")
f.writelines(lines)
f.close()