# 0x16. C - Simple Shell

## Group project


# About this project
- How does a shell work
- How to create processes
- What are the three prototypes of main
- How does the shell use the PATH to find the programs
- The project was done as a team work 2 contributors - ___[STANLEY RATSHILI]()___ and ___[Clement Mphethi]()___ , with the intention of learning more about team colaboration using Git and also enabling work flow with so many files.

# Tasks
0. ___[Betty would be proud](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/0-betty_style.c)___
- This code follows the Betty style guidelines, which typically include rules for indentation (4 spaces), naming conventions (e.g., lowercase with underscores for variables and functions, uppercase with underscores for constants), and other formatting guidelines
1. ___[Simple shell 0.1](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/1-child_process.c)___
 - It displays a prompt, waits for the user to type a command, tokenizes the command into arguments, forks a child process to execute the command, and waits for the child process to finish before displaying the prompt again. It also handles errors and the end of file condition (Ctrl+D) gracefully.
2. ___[Simple shell 0.2](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/2-line.c)___
- This use uses execvp() to execute the command with arguments. It tokenizes the command into arguments based on space, tab, and newline characters, and passes the arguments to execvp() to execute the command along with its arguments.
3. ___[Simple shell 0.3](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/3-handle_the_power.c)___
- This uses access() to check if the command exists in the directories listed in the PATH environment variable before forking a child process to execute it. It also passes the envp argument to execve() to preserve the environment variables, which includes the PATH variable
4. ___[Simple shell 0.4](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/4-built_in.c)___
 - the shell checks if the command is the "exit" built-in command before attempting to execute it. If the command is "exit", the shell exits gracefully with a status code of 0. Otherwise, the shell continues to execute the command as before.
5. ___[Simple shell 1.0](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/5-implement_the_env.c)___
- the shell checks if the command is the "env" built-in command
6. ___[Simple shell 0.1.1](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/6-getline_function.c)___
- The function my_getline() uses static variables to store the buffer, buffer position, and buffer size, so that the buffer can be reused across multiple function calls.
- The function reads data into the buffer using read() system call, but only when the buffer is empty or all the characters in the buffer have been read.
- It copies characters from the buffer to the memory pointed by lineptr one by one, resizing the memory if necessary using realloc().
- The function stops reading when a newline character is encountered, and null-terminates the line using a null character \0.
- It returns the number of bytes read, or -1 on error or end of file, as per the behavior of the standard getline() function.
7. ___[Simple shell 0.2.1](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/7-none_strtok.c)___
- This updated implementation uses a custom tokenization approach that scans the command character by character, skipping leading spaces, and null-terminating the arguments.
8. ___[Simple shell 0.4.1](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/8-handle_argument.c)___
- the shell now checks if the built-in exit command is provided with an argument for the exit status. If an argument is provided, it will be converted to an integer using `atoi
9. ___[setenv, unsetenv](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/9-invironment.c)___
- With this implementation, you can now use the "setenv" and "unsetenv" built-in commands in your custom UNIX command line interpreter to initialize, modify, and remove environment variables, respectively
10. ___[cd](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/10-previous_directory.c)___
- This implementation includes the "cd" built-in command that changes the current directory of the process. It handles different scenarios, such as changing to the home directory when no argument is given, changing to the previous directory when "-" is provided as the argument, updating the "PWD" environment variable with the new directory, and displaying an error message when the specified directory is not found. The implementation also includes the "env" built-in command that displays the current environment variables using the "environ" variable, as well as the "exit" built-in command that exits the shell.
11. ___[;](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/11-semicolon.c)___
- implementation of the env built-in command with support for semicolon (;) as command separator
12. ___[&& and ||](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/12-logical_operators.c)__
- This implementation includes support for the "&&" and "||" shell logical operators. If "&&" is used, the next command will only be executed if the previous command exits with a status of 0 (success). If "||" is used, the next command will only be executed if the previous command exits with a status other than 0 (failure). The implementation also includes the "env" built-in command to print the current environment, as well as the "exit" built-in command to gracefully exit the shell.
13. ___[alias](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/13-alias_value.c)___
- The implementation includes support for defining aliases with the syntax alias name='value', listing all aliases with alias (no arguments), and printing the value of a specific alias with alias name. It also handles updating the value of an existing alias with a new value. Aliases are stored in an array of Alias structures, and the implementation enforces a maximum limit of MAX_ALIASES aliases.
14. ___[Variables](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/14-handle_variable.c)___
- handling of variables "$?" and "" in the execute_command function. When "$?" is encountered in a command, it replaces it with the exit status of the last executed command. When "" is encountered, it replaces it with the current process ID. Additionally, the "env" built-in command has been implemented to print the current environment variables.
15. ___[Comments](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/15-comment.c)___
- With this implementation, any input line starting with '#' character will be treated as a comment and ignored by the interpreter. All other commands will be executed as usual. The 'env' built-in command has been implemented to print the current environment, and comments denoted by '#' character will be ignored during command processing.
16. ___[File as input](https://github.com/HoOdpHarMxcisT/simple_shell/blob/master/16-read_and_process_command.c)___
- allows the user to provide a file as a command line argument. If a file is provided, the shell will read commands from the file, execute them, and then exit. If no file is provided, it will enter interactive mode where it displays a prompt ("simple_shell> ") and reads commands from stdin, allowing the user to interactively enter commands to execute.

> # Authors
>> ___[RATSHILI STANLEY]
>> ___[Clement Mphethi]
