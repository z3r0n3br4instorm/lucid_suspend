#ifndef LACTD_BRIDGE_H
#define LACTD_BRIDGE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <systemd/sd-bus.h>



/**
 * @brief Enable the specified systemd service
 * @param service_name Name of the service to enable
 * @return 0 on success, non-zero on failure
 */
int enable_service(const char *service_name);

/**
 * @brief Disable the specified systemd service
 * @param service_name Name of the service to disable
 * @return 0 on success, non-zero on failure
 */
int disable_service(const char *service_name);

#endif /* LACTD_BRIDGE_H */
