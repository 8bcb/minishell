/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 10:00:00 by asia              #+#    #+#             */
/*   Updated: 2026/01/31 14:55:27 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/exec.h"
#include "env_utils/env_utils.h"
#include "signals.h"

static char	*get_prompt(int exit_status, char *prompt_buf)
{
	if (isatty(STDIN_FILENO))
		snprintf(prompt_buf, 64, "Prompt[%d]> ", exit_status);
	else
		prompt_buf[0] = '\0';
	return (readline(prompt_buf));
}

static void	update_last_status(t_env **env, int exit_status)
{
	char	*tmp;

	tmp = ft_itoa(exit_status);
	if (!tmp)
		return ;
	env_set(env, "?", tmp);
	free(tmp);
}

static void	exec_tree(t_ast *tree, t_env **env, int *exit_status)
{
	if (!tree)
		return ;
	*exit_status = exec_ast(tree, *env);
	update_last_status(env, *exit_status);
	free_ast(tree);
}

static void	process_input(char *rl, t_env **env, int *exit_status)
{
	t_node	*head;
	t_ast	*tree;
	int		is_assignment;
	char	*str;

	is_assignment = 0;
	str = expand_variables(rl, *env);
	if (!str)
		return ;
	head = lexing(str, &is_assignment);
	free(str);
	if (is_assignment == -1 || !head)
		return ;
	tree = parsing(&head);
	exec_tree(tree, env, exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	char	prompt_buf[64];
	int		exit_status;
	t_env	*env;

	(void)argc;
	(void)argv;
	exit_status = 0;
	env = env_init(envp);
	setup_interactive_signals();
	disable_echoctl();
	while (1)
	{
		rl = get_prompt(exit_status, prompt_buf);
		if (!rl)
			break ;
		if (*rl)
			add_history(rl);
		process_input(rl, &env, &exit_status);
		free(rl);
	}
	free_env_list(env);
	return (exit_status);
}
