#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>

int main(int ac __attribute__((unused)), char **av, char **envp);
char *trim(char *str);
void Tok(char *tokI, char **env);
void exec_com(char *com, char **env);
void free_token(char **tokrns, int token_count);
void free_paths_array(char **paths, int num_paths);
char *get_path(char *com_name);
void child_creator(char **tokens, char **env);

#endif /* SHELL_H */
