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
    int c;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF && i < MAX_COMMAND_LENGTH - 1) {
        command[i++] = c;
    }
    command[i] = '\0'; // null-terminate the command
}

int tokenize_command(char *command, char **arguments) {
    int num_arguments = 0;
    int i = 0;
    while (command[i] != '\0' && num_arguments < MAX_ARGUMENTS - 1) {
        // skip leading spaces
        while (command[i] == ' ' || command[i] == '\t') {
            i++;
        }
        if (command[i] == '\0') {
            break; // break if end of command is reached
        }
        arguments[num_arguments++] = &command[i]; // set argument pointer
        // find end of argument
        while (command[i] != ' ' && command[i] != '\t' && command[i] != '\0') {
            i++;
        }
        if (command[i] == '\0') {
            break; // break if end of command is reached
        }
        command[i++] = '\0'; // null-terminate the argument
    }
    arguments[num_arguments] = NULL; // set last argument to NULL for execvp
    return num_arguments;
}

int execute_command(char *command) {
    char *arguments[MAX_ARGUMENTS];
    int num_arguments = tokenize_command(command, arguments);
    
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
