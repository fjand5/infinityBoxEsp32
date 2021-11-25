Import("env")
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
# access to global construction environment
def before_upload(source, target, env):
    print(bcolors.FAIL + bcolors.BOLD +"before_upload===================================================================================================")
    WS2812FX_PATH = env['PROJECT_LIBDEPS_DIR'] + "\\" +  "\\node32s\WS2812FX\\src\\WS2812FX.h"
    try:
        print(bcolors.WARNING + bcolors.BOLD + "Đang hiệu chỉnh file WS2812FX.h" + bcolors.ENDC)

        f = open(WS2812FX_PATH, "r")
        lines = f.readlines()
        f.close()

        for i, line in enumerate(lines):
            if(line.startswith("#define MAX_NUM_SEGMENTS")):
                lines[i] = "#define MAX_NUM_SEGMENTS \t 48\n"
            if(line.startswith("#define MAX_NUM_ACTIVE_SEGMENTS")):
                lines[i] = "#define MAX_NUM_ACTIVE_SEGMENTS \t 48\n"
        f = open(WS2812FX_PATH, "w")
        f.writelines(lines)
        f.close()
    except Exception as e:
        print(bcolors.WARNING + bcolors.BOLD + "Warning: Vui lòng biên dịch lại một lần nữa nếu có lỗi..." + bcolors.ENDC)
env.AddPreAction("upload", before_upload)