/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:06:41 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:04:05 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include <unistd.h>
#include <stdlib.h>

int	count_commands(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (1);
	if (node->type == NODE_PIPE)
		return (count_commands(node->left) + count_commands(node->right));
	return (0);
}

static void	collect_stages_rec(t_ast *node, t_ast **buf, int *idx)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		buf[*idx] = node;
		(*idx)++;
		return ;
	}
	if (node->type == NODE_PIPE)
	{
		collect_stages_rec(node->left, buf, idx);
		collect_stages_rec(node->right, buf, idx);
	}
}

void	collect_pipeline_stages(t_ast *node, t_ast **buf)
{
	int	idx;

	idx = 0;
	collect_stages_rec(node, buf, &idx);
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
