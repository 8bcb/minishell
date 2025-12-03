/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 06:54:16 by asia              #+#    #+#             */
/*   Updated: 2025/12/03 08:41:27 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../signals.h"

int	exec_ast(t_ast *node, t_env *env)
{
	int	status;

	if (!node)
		return (0);
	g_sig = 0;
	/* 1) heredoc preprocess in parent with heredoc signals */
	setup_heredoc_signals();
	status = preprocess_heredocs(node);
	if (status != 0)
	{
		setup_interactive_signals();
		if (status == 130)
			return (130);
		return (1);
	}
	/* 2) execution mode: parent ignores SIGINT/SIGQUIT */
	setup_exec_signals_parent();
	if (node->type == NODE_COMMAND)
		status = exec_command(node, env);
	else if (node->type == NODE_PIPE)
		status = exec_pipeline(node, env);
	else
		status = 1;
	/* 3) back to interactive at prompt */
	setup_interactive_signals();
	return (status);
}
