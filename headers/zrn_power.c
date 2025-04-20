#include "zrn_power.h"
#include <string.h>

bool is_charger_connected(void) {
    FILE *acpi_file;
    char acpi_output[256];
    bool charger_connected = false;

    acpi_file = popen("acpi -a", "r");
    if (acpi_file == NULL) {
        fprintf(stderr, "Failed to run acpi command\n");
        return false;
    }

    if (fgets(acpi_output, sizeof(acpi_output), acpi_file) != NULL) {
        if (strstr(acpi_output, "on-line") != NULL) {
            charger_connected = true;
            return true;
        }
    }

    pclose(acpi_file);
    return false;
}

bool is_lid_open(void) {
    FILE *lid_file;
    char lid_state[256];
    bool lid_open = false;

    lid_file = fopen("/proc/acpi/button/lid/LID0/state", "r");
    if (lid_file == NULL) {
        lid_file = fopen("/proc/acpi/button/lid/LID/state", "r");
        if (lid_file == NULL) {
            fprintf(stderr, "Failed to access lid state\n");
            return true;
        }
    }

    if (fgets(lid_state, sizeof(lid_state), lid_file) != NULL) {
        if (strstr(lid_state, "open") != NULL) {
            lid_open = true;
            fclose(lid_file);
            return  lid_open;
        } else {
            return  false;
        }
    }

    fclose(lid_file);
    return lid_open;
}
