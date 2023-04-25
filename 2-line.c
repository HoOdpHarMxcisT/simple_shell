#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void display_prompt() {
	printf("simple_shell> ");
}

void read_command(char *command) {
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
	printf("\n");
	exit(0);
	}
}

int execute_command(char *command) {
	char *arguments[MAX_ARGUMENTS];
	int num_arguments = 0;
    
	char *token = strtok(command, " \t\n");
	while (token != NULL && num_arguments < MAX_ARGUMENTS - 1) {
	arguments[num_arguments++] = token;
	token = strtok(NULL, " \t\n");
	}
	arguments[num_arguments] = NULL;
    
    
	pid_t pid = fork();
	if (pid < 0) {
	perror("fork");
	return 1;
	} else if (pid == 0) {
        if (execvp(arguments[0], arguments) < 0) {
		perror("execvp");
		exit(1);
	}
	} else {

	int status;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	} else {
		return 1;
	}
	}
	return 0;
}

int main(void) {
	char command[MAX_COMMAND_LENGTH];
	int status;
    
	while (1) {
	display_prompt();
	read_command(command);
	status = execute_command(command);
	}
    
	return 0;
}

