/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:00:00 by asia              #+#    #+#             */
/*   Updated: 2026/01/18 13:38:14 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/exec.h"
#include "env_utils/env_utils.h"
#include "signals.h"

int	main(int argc, char **argv, char **envp)
{
	char    *rl;
	char    prompt_buf[64];
	int     exit_status;
	t_env   *env;
	s_node  *head;
	t_ast   *tree;
	int     isAssignment;

	(void)argc;
	(void)argv;
	exit_status = 0;
	env = env_init(envp);
	setup_interactive_signals();

	while (1)
	{
		if (isatty(STDIN_FILENO))
			snprintf(prompt_buf, sizeof(prompt_buf),
				"Prompt[%d]> ", exit_status);
		else
			prompt_buf[0] = '\0';

		rl = readline(prompt_buf);
		if (!rl)
			break;

		if (*rl)
			add_history(rl);

		head = NULL;
		isAssignment = 0;
		head = tokenizing(rl, &isAssignment);

		if (isAssignment == -1)
		{
			free(rl);
			continue;
		}

		if (head != NULL)
		{
			tree = parsing(&head);
			if (tree != NULL)
			{
				exit_status = exec_ast(tree, env);
				free_ast(tree);
			}
		}

		free(rl);
	}
	return (exit_status);
}
