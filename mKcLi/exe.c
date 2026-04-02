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
        printf("[PARENT] Child finished. Back to VAC OS.\n");
    }
