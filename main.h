#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100 // maximum length of a command
#define MAX_ARGUMENTS 10 // maximum number of arguments in a command

// Function to parse command and arguments from user input
void parse_input(char* input, char* command, char* args[], int* arg_count);

// Function to check if command exists in PATH
int check_command_path(char* command, char* path_entry);

// Function to execute command in a child process
void execute_command(char* full_command, char* args[]);

void display_prompt(): Displays the prompt for the user to enter a command.

void read_command(char *command): Reads a command entered by the user and stores it in the command buffer.

int execute_command(char *command, char **envp): Executes the command entered by the user. It tokenizes the command into arguments, checks if the command exists in the PATH, forks a child process to execute the command, and waits for the child process to finish. It returns the exit status of the child process.

int main(int argc, char *argv[], char *envp[]): The entry point of the program. It contains the main loop for displaying the prompt, reading and executing commands, and handling end of file (Ctrl+D). It returns 0 on successful execution.

#endif /* MAIN_H */
