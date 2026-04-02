void command-run()
  pid_t pid = fork(); // The Great Divide

    if (pid < 0) {
        // 1. The Error Path
        perror("[ERROR] FORK FAILED");
    } 
    else if (pid == 0) {
        // 2. The Child Path (The Worker)
        printf("[CHILD] I am the Clone. Executing command...\n");
        
        char *args[] = {"/IMPO/mKcLi/ls.h", "-l", NULL};
        execvp(args[0], args); // This replaces the child with the 'ls' program
        
        // If execvp fails, this runs:
        perror("[ERROR] EXECVP FAILED");
        _exit(1); 
    } 
    else {
        // 3. The Parent Path (The Architect)
        printf("[PARENT] I created a Child with PID: %d. Waiting...\n", pid);
        wait(NULL); // Wait for the child to finish so we don't get 'Zombies'
          }
// 1. Check for the Master Command
if (strncmp(input, "SYSTEM.EXECUTE", 14) == 0) {
    char *start = strchr(input, '(');
    char *end = strrchr(input, ')');

    if (start && end && start < end) {
        // 2. Extract the "File" name from between ( and )
        int len = end - start - 1;
        char target[256];
        strncpy(target, start + 1, len);
        target[len] = '\0';

        // 3. Force-Route to the Sovereign Header
        printf("[SYSTEM] HOOK ACTIVATED: ROUTING TO /IMPO/mKcLi/SYSTEM.EXECUTE.h\n");
        
        // This runs YOUR specific logic from the mKcLi_ folder
        // We pass the 'target' as the argument to your connected logic
        run_sovereign_execute(target); 
    } else {
        printf("[ERROR] INVALID SYNTAX: USE SYSTEM.EXECUTE(\"file\")\n");
    }
    continue; // Skip the normal fork() path
}
