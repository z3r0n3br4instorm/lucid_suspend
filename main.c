// ztOS: Central Operations Register Engine v4.0
#include "headers/lactd_bridge.h"
#include "headers/zrn_power.h"
#include "headers/xrandr_bridge.h"
#include "headers/sleep_s_negative_one.h"
#include <pthread.h>

void info(const char* data) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "\033[36mINFO\033[0m: %s\n", data);
    fputs(buffer, stdout);
}

void* hud_thread(void* args) {
    for (int i = 0; i >= -1; i++) {
        if (is_charger_connected() == false) {
            system("pkill -SIGSTOP -f 'python3.9 /home/zerone/ztos_home_4.1_beta.py'");
            sleep(5);
            system("pkill -SIGCONT -f 'python3.9 /home/zerone/ztos_home_4.1_beta.py'");
        } else {
            system("pkill -SIGCONT -f 'python3.9 /home/zerone/ztos_home_4.1_beta.py'");
            sleep(10);
        }
    }
    return 0;
}


void* power_thread(void* arg) {
    for (int i = 0; i >= -1; i++) {
        if (is_charger_connected() == true) {
            disable_service("lactd.service");
            info("lactd Disabled !");
            enable_service("nvidia-powerd.service");
            info("nvidia-powerd Enabled !");
            // limit_refresh_to_144hz("DP-2");
            // info("Refresh Rate Set to 144Hz");
        } else {
            enable_service("lactd.service");
            info("lactd Enabled !");
            disable_service("nvidia-powerd.service");
            info("nvidia-powerd Disabled !");
            // limit_refresh_to_60hz("DP-2");
            // info("Refresh Rate Set to 60Hz");
        }
        sleep(5);
    }
    return NULL;
}

void* lid_thread(void* arg) {
    bool previous_lid_state = is_lid_open();

    if (previous_lid_state == true) {
        info("Lid Opened !");
        wake_now();
        system("sudo /usr/bin/nvidia-sleep.sh resume");
        // system("chvt 2");
        // system("xset dpms force off && sleep 1 && xset dpms force on");
	//    sleep(2);
        // system("xdotool key shift+alt+F12");

    } else {
        info("Lid Closed !");
        //system("xdotool key shift+alt+F12");
        //sleep(2);
        // system("chvt 1");
        system("sudo /usr/bin/nvidia-sleep.sh suspend");
        sleep_now();
    }

    while (1) {
        sleep(5);
        bool current_lid_state = is_lid_open();
        if (current_lid_state != previous_lid_state) {
            if (current_lid_state == true) {
                info("Lid Opened !");
                wake_now();
                system("sudo /usr/bin/nvidia-sleep.sh resume");
                // system("chvt 2");
                // system("xset dpms force off && sleep 1 && xset dpms force on");
		        //sleep(2);
                //system("xdotool key shift+alt+F12");
            } else {
                info("Lid Closed !");
                // system("xdotool key shift+alt+F12");
                //sleep(2);
                // system("chvt 1");
                system("sudo /usr/bin/nvidia-sleep.sh suspend");
                sleep_now();
            }
            previous_lid_state = current_lid_state;
        }
    }
    return NULL;
}


int main() {

    info("ztOS Central Operations Register Engine v4.0_BETA_1");
    info("ASUSZRN | Zerone Laboratories");

    pthread_t thread_id;
    int ret;
    info("Initializing Power Thread");
    ret = pthread_create(&thread_id, NULL, power_thread, NULL);
    if (ret != 0) {
        info("An Error Occured !");
        return -1;
    }
    pthread_t lid_thread_id;
    ret = pthread_create(&lid_thread_id, NULL, lid_thread, NULL);
    if (ret != 0) {
        info("An Error Occured !");
        return -1;
    }
    pthread_t hud_thread_id;
    ret = pthread_create(&hud_thread_id, NULL, hud_thread, NULL);
    if (ret != 0) {
        info("An Error Occured !");
        return -1;
    }

    pthread_join(thread_id, NULL);

    return 0;
}
