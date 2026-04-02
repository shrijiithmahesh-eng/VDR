#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void system_execute(const char *filename) {
    // 1. Check if the file exists
    if (access(filename, F_OK) == -1) {
        printf("[ERROR] FILE '%s' NOT FOUND IN VAC OS\n", filename);
        return;
    }

    // 2. Logic Gate: Check if it's a script or binary
    if (strstr(filename, ".txt") || strstr(filename, ".c")) {
        printf("[SYSTEM] OPENING TEXT DATA...\n");
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "cat %s", filename); // Use the system 'cat'
        system(cmd);
    } else {
        // 3. The Fork-and-Run Protocol
        printf("[SYSTEM] EXECUTING BINARY...\n");
        if (fork() == 0) {
            char *args[] = {(char *)filename, NULL};
            execv(filename, args);
            perror("[ERROR] EXECUTION FAILED");
            exit(1);
        } else {
            wait(NULL);
        }
    }
}
