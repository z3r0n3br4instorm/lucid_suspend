#ifndef ZRN_POWER_H
#define ZRN_POWER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * @brief Check if charger is connected
 * @return true if charger is connected, false otherwise
 */
bool is_charger_connected(void);
bool is_lid_open(void);


/**
 * @brief Update services based on charger state
 *
 * If charger is connected:
 *   - Disable lactd.service
 *   - Enable nvidia-powerd.service
 * If charger is disconnected:
 *   - Enable lactd.service
 *   - Disable nvidia-powerd.service
 *
 * @return 0 on success, non-zero on failure
 */
int update_services_by_charger_state(void);


/**
 * @brief Monitor charger state and update services accordingly
 * @param interval_seconds Polling interval in seconds
 * @return 0 on success, non-zero on failure
 */
int monitor_charger_state(int interval_seconds);


#endif /* POWER_H */
