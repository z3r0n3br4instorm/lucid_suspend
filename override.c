#include <stdio.h>
#include<stdlib.h>
#include <string.h>


void process_command(char* command) {
    printf("Manual Override !\n");
    if (strcmp(command, "override_gpu_state") == 0) {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "sudo systemctl stop ztos-core.service");
        system(buffer);
        snprintf(buffer, sizeof(buffer), "sudo systemctl stop lactd.service");
        system(buffer);
        snprintf(buffer, sizeof(buffer), "sudo systemctl stop nvidia-powerd.service");
        system(buffer);
        printf("All GPU Related Services Stopped !\n");
    } else if (strcmp(command, "override_gpu_state_undo") == 0) {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "sudo systemctl start ztos-core.service");
        system(buffer);
        printf("All GPU Related Services Started !\n");

    } else {
        printf("ztOS CORE 4.0 | Manual Override System | Help\n");
        printf("=============================================\n");
        printf("Available Commands:\n\n");
        printf("  override_gpu_state\n");
        printf("    - Stops all GPU-related services (ztos_core, lactd, nvidia-powerd)\n");
        printf("    - Use this when you need to manually control GPU resources\n");
        printf("    - Requires sudo privileges\n\n");
        printf("  override_gpu_state_undo\n");
        printf("    - Restarts all previously stopped GPU-related services\n");
        printf("    - Returns system to normal operation mode\n");
        printf("    - Requires sudo privileges\n\n");
    }
}


int main(int argc, char *argv[]){
    if (argc < 2) {
        process_command("help");
        return 1;
    }
    process_command(argv[1]);
    return 0;
}
