/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:35:00 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 10:02:07 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/exec.h"
#include "env_utils.h"
#include "signals.h"
#include "./test_node.c"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	int		exit_status;
	t_env	*env;
	char	prompt_buf[64];
	char	**argv_split;
	t_ast	*node;

	(void)argc;
	(void)argv;
	exit_status = 0;
	env = env_init(envp);
	setup_interactive_signals();
	while (1)
	{
		if (isatty(STDIN_FILENO))
			snprintf(prompt_buf, sizeof(prompt_buf),
				"minishell[%d]> ", exit_status);
		else
			prompt_buf[0] = '\0';
		rl = readline(prompt_buf);
		if (!rl)
			break ;
		if (*rl)
			add_history(rl);
		argv_split = ft_split(rl, ' ');
		if (argv_split && argv_split[0])
		{
			node = build_mock_ast_from_argv(argv_split);
			if (node)
				exit_status = exec_ast(node, env);
		}
		else
			free(argv_split);
		free(rl);
	}
	return (exit_status);
}

//lexing/parsing main
// int main(void) 
// {
// 	char *rl;
// 	s_node *head;
// 	int status;

// 	status = 0;
// 	head = (s_node *)malloc(sizeof(s_node));
// 	if (!head)
// 		return 1;
// 	printf("Head: %s\n", head->val.value);
// 	while (1) {
// 		rl = readline("Prompt > ");
// 		status = scanInput(rl, head);
// 		//if (status == -1)
// 			//free memory and exit
// 		printList(head);
// 	}
// }