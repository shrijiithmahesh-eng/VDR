include <stdio.h>

// Echo program: prints all command-line arguments separated by spaces
int main(int argc, char *argv[]) {
    // If no arguments are given, just print a newline
    if (argc <= 1) {
        printf("\n");
        return 0;
    }

    // Loop through arguments starting from argv[1] (skip program name)
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" "); // Add space between arguments
        }
    }

    printf("\n"); // End with newline
    return 0;
}
