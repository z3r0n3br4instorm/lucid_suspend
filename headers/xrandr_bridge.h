#ifndef XRANDR_BRIDGE_H
#define XRANDR_BRIDGE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>



int limit_refresh_to_60hz(const char *display_name);

int limit_refresh_to_144hz(const char *display_name);

#endif
