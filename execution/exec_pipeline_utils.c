/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:06:41 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 10:15:02 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include <unistd.h>
#include <stdlib.h>

/*
** count_commands:
**   Recursively count the number of NODE_COMMANDs in a pipe tree.
**   NODE_PIPE is an internal node, left/right are stages.
*/
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

/*
** Helper for collect_pipeline_stages: in-order traversal of a pipe tree.
** We assume left-associative: (((cmd1 | cmd2) | cmd3) | cmd4)
** So the buffer will be [cmd1, cmd2, cmd3, cmd4].
*/
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

/*
** collect_pipeline_stages:
**   Fills buf[0..n-1] with NODE_COMMAND pointers in left-to-right order.
**   Caller must have allocated buf with size == count_commands(pipe_node).
*/
void	collect_pipeline_stages(t_ast *node, t_ast **buf)
{
	int	idx;

	idx = 0;
	collect_stages_rec(node, buf, &idx);
}

/*
** create_pipes:
**   Create number_of_pipes pipes; pipes is an array [number_of_pipes][2].
**   Returns 0 on success, 1 on error.
*/
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

/*
** dup_pipeline_ends:
**   For stage "index" in total "n_stages" with "n_pipes" pipes:
**     - if index > 0, stdin comes from previous pipe read end
**     - if index < n_stages-1, stdout goes to current pipe write end
**   Used in each child before executing the command.
*/
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
