#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void command_run() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("[ERROR] FORK FAILED");
    } 
    else if (pid == 0) {
        printf("[CHILD] I am the Clone. Executing command...\n");
        char *args[] = {"/IMPO/mKcLi/ls.bin", "-l", NULL};
        execvp(args[0], args);
        perror("[ERROR] EXECVP FAILED");
        _exit(1); 
    } 
    else {
        printf("[PARENT] I created a Child with PID: %d. Waiting...\n", pid);
        wait(NULL);
    }
}

void SYSexe(char *input) {
    if (strncmp(input, "SHUTDOWN", 8) == 0) {
        char *start = strchr(input, '(');
        char *end = strrchr(input, ')');
        if (start && end && start < end) {
            int len = end - start - 1;
            if (len >= 256) { printf("[ERROR] ARGUMENT TOO LONG\n"); return; }
            char target[256];
            strncpy(target, start + 1, len);
            target[len] = '\0';
            printf("[SYSTEM] HOOK ACTIVATED: ROUTING TO /IMPO/mKcLi/SHUTDOWN.h\n");
            run(target);
        } else {
            printf("[ERROR] INVALID COMMAND\n");
        }
        return;
    }

    if (strncmp(input, "SYSTEM.EXECUTE", 14) == 0) {
        char *start = strchr(input, '(');
        char *end = strrchr(input, ')');
        if (start && end && start < end) {
            int len = end - start - 1;
            if (len >= 256) { printf("[ERROR] ARGUMENT TOO LONG\n"); return; }
            char target[256];
            strncpy(target, start + 1, len);
            target[len] = '\0';
            printf("[SYSTEM] HOOK ACTIVATED: ROUTING TO /IMPO/mKcLi/SYSTEM.OPEN.h\n");
            run_sovereign_execute(target);
        } else {
            printf("[ERROR] INVALID SYNTAX: USE SYSTEM.EXECUTE(\"file\")\n");
        }
        return;
    }

    // Default: run as normal command
    command_run();
}
