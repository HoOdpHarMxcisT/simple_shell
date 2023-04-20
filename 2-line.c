#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int execute_command(char *command) {
    char *arguments[MAX_ARGUMENTS];
    int num_arguments = 0;
    
    // tokenize the command into arguments
    char *token = strtok(command, " \t\n");
    while (token != NULL && num_arguments < MAX_ARGUMENTS - 1) {
        arguments[num_arguments++] = token;
        token = strtok(NULL, " \t\n");
    }
    arguments[num_arguments] = NULL; // set last argument to NULL for execvp
    
    // fork a child process to execute the command
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // child process
        if (execvp(arguments[0], arguments) < 0) {
            perror("execvp");
            exit(1);
        }
    } else {
        // parent process
        int status;
        waitpid(pid, &status, 0); // wait for child process to finish
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return 1;
        }
    }
    return 0;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    int status;
    
    while (1) {
        display_prompt();
        read_command(command);
        status = execute_command(command);
    }
    
    return 0;
}

