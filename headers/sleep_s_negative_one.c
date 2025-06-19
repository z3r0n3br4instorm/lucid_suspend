#include "sleep_s_negative_one.h"
#include <string.h>
#include <signal.h>

int sleep_now() {
    // SIGSTOP STUFF
    const char *excluded_services[] = {
        "ztos-core.service",
        "sshd.service",
        "auto-cpufreq.service"
        "nvidia-persistenced.service",
        "nvidia-powerd.service",
        "nvidia-hibernate.service",
        "nvidia-resume.service",
        "nvidia-suspend.service",
        "nvidia-suspend-then-hibernate.service",
        "lactd.service",
        "systemd-journald.service",
        "systemd-udevd.service",
        "systemd-logind.service",
        "systemd-timesyncd.service",
        "btop",
        "sshd",
        "ssh"
    };
    int num_excluded = sizeof(excluded_services) / sizeof(excluded_services[0]);
    FILE *fp;
    char line[256];
    char cmd[] = "systemctl list-units --type=service --all --no-pager --plain | awk '{print $1}'";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        return -1;
    }

    // For each service, check if it's excluded and send SIGSTOP if not
    while (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        if (strstr(line, ".service") == NULL || strlen(line) == 0) {
            continue;
        }

        int exclude = 0;
        for (int i = 0; i < num_excluded; i++) {
            if (strcmp(line, excluded_services[i]) == 0) {
                exclude = 1;
                break;
            }
        }

        if (!exclude) {
            char kill_cmd[300];
            sprintf(kill_cmd, "systemctl kill --signal=SIGSTOP %s", line);
            system(kill_cmd);
        }
    }

    pclose(fp);
    return 0;
}

int wake_now() {
    FILE *fp;
    char line[256];
    char cmd[] = "systemctl list-units --type=service --all --no-pager --plain | awk '{print $1}'";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        return -1;
    }

    // For each service, remove the SIGSTOP condition
    while (fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        if (strstr(line, ".service") == NULL || strlen(line) == 0) {
            continue;
        }

        // Send a wake signal to all services
        char wake_cmd[300];
        sprintf(wake_cmd, "systemctl kill --signal=SIGCONT %s", line);
        system(wake_cmd);
    }

    pclose(fp);
    return 0;
}
