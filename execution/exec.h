#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"
#include "./builtins/builtins.h"

int exec_ast(t_ast *node, t_env *env);

int exec_command(t_ast *cmd, t_env *env);

int     exec_external(char **argv, t_env *env);
int     spawn_execve(const char *path, char **argv);
char    *resolve_in_path(char *command);

// exec_external_utils.c
void        free_split(char **split_array);
char        *join_path(const char *dir, const char *command);
int         status_from_wait(int status);
void        print_cmd_error(const char *command, const char *message);
int         contains_slash(const char *str);

#endif