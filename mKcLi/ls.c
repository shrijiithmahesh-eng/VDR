#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>   // For opendir(), readdir(), closedir()
#include <errno.h>    // For errno
#include <string.h>   // For strerror()

// Function to list files in a directory
void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // Try to open the directory
    dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "Error: Cannot open directory '%s': %s\n", path, strerror(errno));
        return;
    }

    printf("Listing files in: %s\n", path);

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    if (closedir(dir) != 0) {
        fprintf(stderr, "Warning: Failed to close directory '%s': %s\n", path, strerror(errno));
    }
}

int main(int argc, char *argv[]) {
    // If no argument is given, list current directory
    if (argc == 1) {
        list_files(".");
    }
    // If a directory path is given
    else if (argc == 2) {
        list_files(argv[1]);
    }
    // Too many arguments
    else {
        fprintf(stderr, "Usage: %s [directory_path]\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
