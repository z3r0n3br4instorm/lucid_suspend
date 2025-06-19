#include "xrandr_bridge.h"


int limit_refresh_to_60hz(const char *display_name) {
    char command[256];
    snprintf(command, sizeof(command), "xrandr --output %s --mode 1920x1080 --rate 60", display_name);
    return system(command);
}

int limit_refresh_to_144hz(const char *display_name) {
    char command[256];
    snprintf(command, sizeof(command), "xrandr --output %s --mode 1920x1080 --rate 144", display_name);
    return system(command);
}
