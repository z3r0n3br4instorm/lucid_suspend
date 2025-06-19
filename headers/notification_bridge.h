#ifndef NOTIFICATION_BRIDGE_H
#define NOTIFICATION_BRIDGE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <systemd/sd-bus.h>

int send_notification(const char *summary, const char *body);

#endif
