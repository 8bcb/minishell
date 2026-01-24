/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:47:35 by jziola            #+#    #+#             */
/*   Updated: 2026/01/24 14:42:00 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"
# include "./builtins/builtins.h"

typedef struct s_pipeline
{
	int		n_stages;
	int		n_pipes;
	t_ast	**stages;
	int		(*pipes)[2];
	pid_t	*pids;
}	t_pipeline;

int		exec_ast(t_ast *node, t_env *env);

int		exec_command(t_ast *cmd, t_env *env);
void	run_child_command(t_ast *cmd, t_env *env);

int		exec_pipeline(t_ast *pipe_node, t_env *env);

void	close_all_pipes(int (*pipes)[2], int number_of_pipes);
int		count_commands(t_ast *pipe_node);
void	collect_pipeline_stages(t_ast *node, t_ast **buf);

int		create_pipes(int (*pipes)[2], int number_of_pipes);

void	dup_pipeline_ends(
			int (*pipes)[2],
			int n_pipes,
			int index,
			int n_stages
			);

void	print_cmd_error(const char *command, const char *message);
int		preprocess_heredocs(t_ast *node);
void	free_ast(t_ast *node);
int		get_last_status(pid_t *pids, int n_stages);

#endif
