/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:57 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 17:28:48 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"

extern volatile sig_atomic_t	g_sig;

static int	preprocess_heredoc_for_cmd(t_ast *cmd)
{
	int	fd;

	if (!cmd || !cmd->heredoc_tmp)
		return (0);
	fd = open_heredoc_fd(cmd->heredoc_tmp);
	if (fd < 0)
	{
		if (g_sig == SIGINT)
			return (130);
		return (1);
	}
	cmd->heredoc_fd = fd;
	return (0);
}

int	preprocess_heredocs(t_ast *node)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (preprocess_heredoc_for_cmd(node));
	if (node->type == NODE_PIPE)
	{
		status = preprocess_heredocs(node->left);
		if (status != 0)
			return (status);
		return (preprocess_heredocs(node->right));
	}
	return (0);
}
