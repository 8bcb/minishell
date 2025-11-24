/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:40:14 by pkosciel          #+#    #+#             */
/*   Updated: 2025/11/19 08:49:04 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/exec.h"
#include "./test_node.c"

int main(void) 
{
	char	*rl;
	int		exit_status;
	
	while (1) {
		char prompt_buf[64];
        if (isatty(STDIN_FILENO))
            snprintf(prompt_buf, sizeof(prompt_buf), "minishell[%d]> ", exit_status);
        else
            prompt_buf[0] = '\0';
		rl = readline(prompt_buf);
		if (!rl) break;
		if (*rl) add_history(rl);
		char	**argv;
		t_ast	*node;

		argv = ft_split(rl, ' ');
		if (argv && argv[0])
		{
			node = build_mock_ast_from_argv(argv);
			if (node)
				exit_status = exec_ast(node, NULL);
		}
		else
			free(argv);
		free(rl);
		// scanInput(rl);
		//parseInput
		//execute
	}
	return exit_status;
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