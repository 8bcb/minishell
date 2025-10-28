#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"
#include "../utils.h"
#include "./builtins/builtins.h"

int exec_ast(t_ast *node, t_env);
int exec_command(t_ast *cmd, t_env);

#endif