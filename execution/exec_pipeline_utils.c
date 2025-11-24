/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:06:41 by asia              #+#    #+#             */
/*   Updated: 2025/11/24 09:12:39 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	count_commands(t_ast *pipe_node)
{
	int	count;

	count = 0;
	while (pipe_node && pipe_node->type == NODE_PIPE)
	{
		count++;
		pipe_node = pipe_node->right;
	}
	if (pipe_node)
		count++;
	return (count);
}

void	collect_pipeline_stages(t_ast *node, t_ast **buf)
{
	int	i;

	i = 0;
	while (node && node->type == NODE_PIPE)
	{
		buf[i] = node->left;
		node = node->right;
		i++;
	}
	if (node)
		buf[i] = node;
}

int	create_pipes(int (*pipes)[2], int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		if (pipe(pipes[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	spawn_pipeline_children(int n_stages, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < n_stages)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

void	dup_pipeline_ends(int (*pipes)[2], int n_pipes,
			int index, int n_stages)
{
	if (n_pipes <= 0)
		return ;
	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index < n_stages - 1)
		dup2(pipes[index][1], STDOUT_FILENO);
}