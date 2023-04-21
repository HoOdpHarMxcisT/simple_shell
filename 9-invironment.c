#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100 // maximum length of a command
#define MAX_ARGUMENTS 10 // maximum number of arguments in a command

extern char **environ; // global variable to access the environment

void display_prompt() {
    printf("simple_shell> "); // display the prompt
}

void read_command(char *command) {
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
        printf("\n"); // print new line after end of file (Ctrl+D)
        exit(0); // exit gracefully on end of file
    }
}

int execute_command(char *command, char **envp) {
    char *arguments[MAX_ARGUMENTS];
    int num_arguments = 0;
    
    // tokenize the command into arguments
    char *token = strtok(command, " \t\n");
    while (token != NULL && num_arguments < MAX_ARGUMENTS - 1) {
        arguments[num_arguments++] = token;
        token = strtok(NULL, " \t\n");
    }
    arguments[num_arguments] = NULL; // set last argument to NULL for execvp
    
    // check if the command is the exit built-in
    if (strcmp(arguments[0], "exit") == 0) {
        exit(0); // exit gracefully
    }
    // check if the command is the env built-in
    else if (strcmp(arguments[0], "env") == 0) {
        // print the current environment
        for (int i = 0; envp[i] != NULL; i++) {
            printf("%s\n", envp[i]);
        }
        return 0;
    }
    // check if the command is the setenv built-in
    else if (strcmp(arguments[0], "setenv") == 0) {
        // check for correct number of arguments
        if (num_arguments != 3) {
            fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            return 1;
        }
        // set or modify the environment variable
        if (setenv(arguments[1], arguments[2], 1) != 0) {
            perror("setenv");
            return 1;
        }
        return 0;
    }
    // check if the command is the unsetenv built-in
    else if (strcmp(arguments[0], "unsetenv") == 0) {
        // check for correct number of arguments
        if (num_arguments != 2) {
            fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            return 1;
        }
        // remove the environment variable
        if (unsetenv(arguments[1]) != 0) {
            perror("unsetenv");
            return 1;
        }
        return 0;
    }
    
    // check if the command exists in the PATH
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    token = strtok(path_copy, ":");
    while (token != NULL) {
        char command_path[MAX_COMMAND_LENGTH + 1];
        snprintf(command_path, sizeof(command_path), "%s/%s", token, arguments[0]);
        if (access(command_path, X_OK) == 0) {
            // fork a child process to execute the command
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                free(path_copy);
                return 1;
            } else if (pid == 0) {
                // child process
                execv(command_path, arguments);
                // if execv returns, it failed
                perror(arguments[0]);
                free(path_copy);
                exit(1);
            } else {
                // parent process
                int status;
                waitpid(pid, &status, 0); // wait for child to finish
                free(path_copy);
                return WEXITSTATUS(status);
            }
        }
        token = strtok(NULL, ":");
    }
    free(path_copy);
    
    // command not found
    fprintf(stderr, "Command not found: %s\n", arguments[0]);
    return 1;
}

int main() {
    char command[MAX_COMMAND_LENGTH + 1];
    
    while (1) {
        display_prompt();
        read_command(command);
        int result = execute_command(command, environ);
        if (result != 0) {
            fprintf(stderr, "Command failed with status %d\n", result);
        }
    }
    
    return 0;
}

