#ifndef EXEC_H
# define EXEC_H

#include "../minishell.h"
#include "./builtins/builtins.h"

int exec_ast(t_ast *node, t_env *env);

int exec_command(t_ast *cmd, t_env *env);
void    run_child_command(t_ast *cmd, t_env *env);

int exec_pipeline(t_ast *pipe_node, t_env *env);
int	count_commands(t_ast *pipe_node);
void	collect_pipeline_stages(t_ast *node, t_ast **buf);
int	create_pipes(int (*pipes)[2], int number_of_pipes);
int	spawn_pipeline_children(int n_stages, pid_t *pids);
void	dup_pipeline_ends(int (*pipes)[2], int n_pipes,
			int index, int n_stages);

void    print_cmd_error(const char *command, const char *message);

#endif