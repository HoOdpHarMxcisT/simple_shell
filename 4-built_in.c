#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100 // maximum length of a command
#define MAX_ARGUMENTS 10 // maximum number of arguments in a command

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
                if (execve(command_path, arguments, envp) < 0) {
                    perror("execve");
                    free(path_copy);
                    exit(1);
                }
            } else {
                // parent process
                int status;
                waitpid(pid, &status, 0); // wait for child process to finish
                free(path_copy);
                if (WIFEXITED(status)) {
                    return WEXITSTATUS(status);
                } else {
                    return 1;
                }
            }
        }
        token = strtok(NULL, ":");
    }
    free(path_copy);
    
    // command not found in the PATH
    printf("Command not found: %s\n", arguments[0]);
    return 1;
}

int main(int argc, char *argv[], char *envp[]) {
    char command[MAX_COMMAND_LENGTH];
    int status;
    
    while (1) {
        display_prompt();
        read_command(command);
        status = execute_command(command, envp);
    }
    
    return 0;
}

