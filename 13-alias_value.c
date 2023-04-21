#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100 // maximum length of a command
#define MAX_ARGUMENTS 10 // maximum number of arguments in a command
#define MAX_ALIASES 10 // maximum number of aliases

extern char **environ; // external reference to the current environment

typedef struct Alias {
    char name[MAX_COMMAND_LENGTH];
    char value[MAX_COMMAND_LENGTH];
} Alias;

Alias aliases[MAX_ALIASES]; // array to store aliases
int num_aliases = 0; // number of defined aliases

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
    if (strcmp(arguments[0], "env") == 0) {
        // print the current environment
        char **env = envp;
        while (*env != NULL) {
            printf("%s\n", *env++);
        }
        return 0;
    }
    
    // check if the command is the alias built-in
    if (strcmp(arguments[0], "alias") == 0) {
        // if no arguments provided, print list of all aliases
        if (num_arguments == 1) {
            for (int i = 0; i < num_aliases; i++) {
                printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            }
            return 0;
        }
        
        // if one or more arguments provided, handle alias commands
        for (int i = 1; i < num_arguments; i++) {
            char *arg = arguments[i];
            char *name = strtok(arg, "=");
            char *value = strtok(NULL, " \t\n");
            
            // check if alias with same name already exists
            int existing_alias_index = -1;
            for (int j = 0; j < num_aliases; j++) {
                if (strcmp(aliases[j].name, name) == 0) {
                    existing_alias_index = j;
                    break;
                }
            }
            
            if (value == NULL) {
                // if value not provided, print alias value
                if (existing_alias_index >= 0) {
                    printf("%s='%s'\n", aliases[existing_alias_index].name, aliases[existing_alias_index].value);
                } else {
                    printf("Alias not found: %s\n", name);
                }
            } else {
                // if
                // value provided, create/update alias
                if (existing_alias_index >= 0) {
                    // update existing alias
                    strncpy(aliases[existing_alias_index].value, value, MAX_COMMAND_LENGTH - 1);
                } else {
                    // create new alias
                    if (num_aliases == MAX_ALIASES) {
                        printf("Maximum number of aliases reached.\n");
                    } else {
                        Alias new_alias;
                        strncpy(new_alias.name, name, MAX_COMMAND_LENGTH - 1);
                        strncpy(new_alias.value, value, MAX_COMMAND_LENGTH - 1);
                        aliases[num_aliases++] = new_alias;
                    }
                }
            }
        }
        
        return 0;
    }
    
    // check if the command is an alias
    int alias_index = -1;
    for (int i = 0; i < num_aliases; i++) {
        if (strcmp(arguments[0], aliases[i].name) == 0) {
            alias_index = i;
            break;
        }
    }
    
    if (alias_index >= 0) {
        // if alias found, execute the aliased command
        strncpy(command, aliases[alias_index].value, MAX_COMMAND_LENGTH - 1);
        return execute_command(command, envp);
    }
    
    // fork a child process to execute the command
    pid_t pid = fork();
    if (pid < 0) {
        printf("Failed to fork process.\n");
        return -1;
    } else if (pid == 0) {
        // child process
        execvp(arguments[0], arguments);
        printf("Command not found: %s\n", arguments[0]);
        exit(0);
    } else {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    
    while (1) {
        display_prompt();
        read_command(command);
        int exit_status = execute_command(command, environ);
        printf("Exit status: %d\n", exit_status);
    }
    
    return 0;
}
