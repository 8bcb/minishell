/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:00:00 by asia              #+#    #+#             */
/*   Updated: 2025/12/19 08:51:59 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/exec.h"
#include "env_utils.h"
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
		// local vriable expansion
		if (!rl)
			break;

		if (*rl)
			add_history(rl);

		head = NULL;
		isAssignment = 0;
		head = tokenizing(rl, &isAssignment);
		free(rl);

		if (isAssignment == -1)
			continue;
		//else if (isAssignment == 1)
		//	add__to_local_variables

		if (head != NULL)
		{
			print_list(head);
			tree = parsing(&head);
			print_tree(tree, 0);
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
