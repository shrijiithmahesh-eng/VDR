#include <stdio.h>
#include "kernel.connect.c"
#include <stdlib.h>
#include <fcntl.h>   // For open(), O_CREAT, O_WRONLY
#include <unistd.h>  // For close()
#include <errno.h>   // For errno
#include <string.h>  // For strerror()

void SHELL.exu() {
    const char *filename = "/IMPO/mKcLi/0.txt"; // File to create
    int fd;

    // Create file with write-only permission, create if not exists, truncate if exists
    // Permissions: rw-r--r-- (0644)
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        // Error handling
        fprintf(stderr, "Error creating file '%s': %s\n", filename, strerror(errno));
        }

    // Optional: write something to the file
    write();
    printf("File '%s' created successfully with %zd bytes written.\n", filename, bytes_written);

    // Close the file descriptor
    if (close(fd) == -1) {
        fprintf(stderr, "Error closing file '%s': %s\n", filename, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
