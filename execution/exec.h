#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"
#include "./builtins/builtins.h"

int exec_ast(t_ast *node, t_env *env);
int exec_command(t_ast *cmd, t_env *env);
int exec_builtin(t_ast *cmd, t_env *env);
int is_builtin(char *cmd_name);

#endif