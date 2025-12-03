/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:00:00 by asia              #+#    #+#             */
/*   Updated: 2025/12/03 08:54:24 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

static void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_command_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->argv)
		free_str_array(node->argv);
	if (node->infile)
	{
		free_str_array(node->infile);
	}
	if (node->outfile)
	{
		free_str_array(node->outfile);
	}
	if (node->heredoc_tmp)
		free(node->heredoc_tmp);
	if (node->heredoc_fd >= 0)
		close(node->heredoc_fd);
	free(node);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		free_ast(node->left);
		free_ast(node->right);
		free(node);
	}
	else
		free_command_node(node);
}
