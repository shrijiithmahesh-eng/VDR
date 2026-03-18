#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Editor(char *filename) {
    char command[512];
    // %s is the "portal" that lets the filename pass through to the EDITOR
    sprintf(command, "./EDITOR %s", filename); 
    system(command);
}

void Attach() {
    char input[100]; 
    printf("Welcome to TICILEL\n");
    printf("TCIR> "); 

    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0; // Strip newline

        // Look for the specific flag
        char *flag = "--OPEN --";
        char *found = strstr(input, flag);

        if (found) {
            // Move the pointer to the start of the actual filename
            char *filename = found + strlen(flag);
            printf("\nOpening Editor for: %s\n", filename);
            Editor(filename);
        } else {
            printf("\nUnknown command. Usage: TICILE --OPEN --FILENAME.OSP\n");
        }
    }
}

int main() {
    Attach();
    return 0;
}
