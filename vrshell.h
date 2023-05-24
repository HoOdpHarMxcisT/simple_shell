#ifndef VRSHELL_H
#define VRSHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

char *read_line(int n);
int count_words(char *str, char *delim);
char **parse_str(char *str, char *delim, int n);
int executearg(char **arg);
char *_strcat(char *dest, char *src);
int _strlen(char *str);
int _strncmp(char *s1, char *s2, int n);
char *_strncpy(char *dest, char *src, int from, int n);
char *_strdup(char *s);
char *_getenv(const char *name);
char **_paths(void);
char *_finder(char **paths, char *cmd);
extern char **environ;
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_dptr(char **ptr);
int _putchar(char c);
int checkbi(char **tokens);
int runbi(char **tokens);
char *pathfinder(char **arg);
void badcom(int errorstatus, int count, char *cmd);
void print_number(int n);
int stderr_pc(char c);
char *pstart(char *allpaths);
char *pend(char *allpaths);

#endif /* VRSHELL_H */