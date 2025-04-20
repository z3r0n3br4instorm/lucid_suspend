#include "lactd_bridge.h"

int disable_service(const char *service_name) {
    char command[256];
    snprintf(command, sizeof(command), "sudo systemctl disable --now %s", service_name);
    return system(command);
}

int enable_service(const char *service_name) {
    char command[256];
    snprintf(command, sizeof(command), "sudo systemctl enable --now %s", service_name);
    return system(command);
}
