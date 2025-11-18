#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"
#include "./builtins/builtins.h"

int exec_ast(t_ast *node, t_env *env);

int exec_command(t_ast *cmd, t_env *env);
void    run_child_command(t_ast *cmd, t_env *env);

int exec_pipeline(t_ast *pipe_node, t_env *env);

#endif