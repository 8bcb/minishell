/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:40:14 by pkosciel          #+#    #+#             */
/*   Updated: 2025/11/17 06:52:44 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/exec.h"
#include "./test_node.c"

// TODO: remove - only for dev purposes
int free_node(t_ast *n)
{
    int i = 0;

    if (!n) return 0;

    if (n->argv) {
        while (n->argv[i]) free(n->argv[i++]);
        free(n->argv);
    }
    if (n->infile) {
        if (n->infile[0]) free(n->infile[0]);
        free(n->infile);
    }
    if (n->outfile) {
        if (n->outfile[0]) free(n->outfile[0]);
        free(n->outfile);
    }
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
			t_ast *node = mock_node_from_argv(argv);
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