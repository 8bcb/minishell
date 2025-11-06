/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:40:14 by pkosciel          #+#    #+#             */
/*   Updated: 2025/11/05 07:49:32 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/exec.h"

// TODO: remove - only for test purposes
static t_ast *mock_node(char **argv)
{
	t_ast *node = ft_calloc(1, sizeof(*node));
	node->type = NODE_COMMAND;
	node->argv = argv;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// TODO: remove - only for dev purposes
int free_node(t_ast *n)
{
	int		i;
	char	**argv;
	i = 0;

	if (!n)
		return 0;
	argv = n->argv;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	free(n);
	return 1;
}

int main(void) 
{
	char	*rl;
	int		exit_status;
	
	while (1) {
		char prompt_buf[64];
        // Show status in the prompt when interactive; stay silent when piped
        if (isatty(STDIN_FILENO))
            snprintf(prompt_buf, sizeof(prompt_buf), "minishell[%d]> ", exit_status);
        else
            prompt_buf[0] = '\0';
		rl = readline(prompt_buf);
		if (!rl) break;
		if (*rl) add_history(rl);
		char **argv = ft_split(rl, ' ');
		if (argv && argv[0])
		{
			t_ast *node = mock_node(argv);
			exit_status = exec_ast(node, NULL);
			(void)exit_status;
			free_node(node);
		}
		else
		{
			free(argv);
		}
		free(rl);
		// scanInput(rl);
		//parseInput
		//execute
	}
	return exit_status;
}