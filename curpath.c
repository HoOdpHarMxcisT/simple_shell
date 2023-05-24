#include "shell.h"
/**
 * pstart - append current dir to beginning of path env
 * @allpaths: the current path env
 *
 * Return: full appended path
 */
char *pstart(char *allpaths)
{
	int len_cwd, len_allpaths, new_len;
	char *cwd;

	cwd = getcwd(NULL, 0);
	len_cwd = _strlen(cwd);
	len_allpaths = _strlen(allpaths);
	new_len = len_cwd + len_allpaths;
	cwd = _realloc(cwd, len_cwd, (new_len + 1));
	_strcat(cwd, allpaths);

	return (cwd);
}
/**
 * pend - append current working directory to end of PATH
 * @allpaths: current path env
 *
 * Return: PATH with command appended
 */
char *pend(char *allpaths)
{
	int len_allpaths, len_cwd, new_len;
	char *cwd;

	cwd = getcwd(NULL, 0);
	len_cwd = _strlen(cwd);
	len_allpaths = _strlen(allpaths);
	new_len = len_allpaths + len_cwd;
	allpaths = _realloc(allpaths, len_allpaths, (new_len + 1));
	_strcat(allpaths, cwd);

	return (allpaths);
}