
#include "shell.h"
/**
  * executearg - execute argument
  * @arg: argument to execute
  *
  * Return: 0
  */

int executearg(char **arg)
{
	pid_t c_pid, pid;
	int status, ac;
	char *path;

	path = pathfinder(arg);
	ac = access(path, F_OK);
	if (ac != 0)
		return (127);
	ac = access(path, X_OK);
	if (ac != 0)
		return (126);
	c_pid = fork();
	if (c_pid == 0)
	{
		execve(path, arg, NULL);
		return (errno);
	}
	else if (c_pid > 0)
	{
		pid = waitpid(c_pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (pid < 0)
			return (errno);
	}
	else
		return (errno);

	return (status);
}