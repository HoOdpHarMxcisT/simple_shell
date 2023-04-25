#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_pos = 0;
    static ssize_t buffer_size = 0;
    ssize_t bytes_read = 0;
    ssize_t total_bytes_read = 0;
    char c;

    if (lineptr == NULL || n == NULL) {
        return -1;
    }

    if (*lineptr == NULL || *n == 0) {
        return -1;
    }

    while (1) {
        // Read more data into buffer if buffer is empty
        if (buffer_pos >= buffer_size) {
            bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                // End of file or error
                break;
            }
            buffer_pos = 0;
            buffer_size = bytes_read;
        }

        // Copy character from buffer to lineptr
        c = buffer[buffer_pos++];
        (*lineptr)[total_bytes_read++] = c;

        // Resize lineptr if necessary
        if (total_bytes_read >= *n) {
            *n *= 2;
            *lineptr = realloc(*lineptr, *n);
            if (*lineptr == NULL) {
                return -1; // Memory allocation error
            }
        }

        // Break loop when newline is encountered
        if (c == '\n') {
            break;
        }
    }

    // Null-terminate lineptr
    (*lineptr)[total_bytes_read] = '\0';

    // Return -1 on error or end of file, otherwise return number of bytes read
    return (total_bytes_read == 0 && bytes_read <= 0) ? -1 : total_bytes_read;
}

