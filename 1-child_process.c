#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> // Added for strlen

int main() {
    while (1) {
        // Display prompt
        printf("simple_shell$ ");

        // Read input from user
        char command[256];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            // Exit loop if end of file (Ctrl+D)
            break;
        }

        // Remove newline character from command
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            execlp(command, command, NULL);

            // Print error message if command not found
            printf("simple_shell: %s: command not found\n", command);
            exit(1);
        } else if (pid > 0) {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        } else {
            // Error forking process
            printf("simple_shell: error forking process\n");
            exit(1);
        }
    }

    return 0;
}

