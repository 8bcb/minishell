/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:00:00 by asia              #+#    #+#             */
/*   Updated: 2025/11/18 10:58:46 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "./exec_external/exec_external.h"

static int	count_commands(t_ast *pipe_node)
{
	int	count;

	count = 0;
	while (pipe_node && pipe_node->type == NODE_PIPE)
	{
		count++;
		pipe_node = pipe_node->right;
	}
	if (pipe_node)
		count++;
	return (count);
}

static void	collect_pipeline_stages(t_ast *node, t_ast **buf)
{
	int	i;

	i = 0;
	while (node && node->type == NODE_PIPE)
	{
		buf[i] = node->left;
		node = node->right;
		i++;
	}
	if (node)
		buf[i] = node;
}

static int	create_pipes(int (*pipes)[2], int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		if (pipe(pipes[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

static void	close_all_pipes(int (*pipes)[2], int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	dup_pipeline_ends(int (*pipes)[2], int n_pipes,
			int index, int n_stages)
{
	if (n_pipes <= 0)
		return ;
	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index < n_stages - 1)
		dup2(pipes[index][1], STDOUT_FILENO);
}

static int	spawn_pipeline_children(int n_stages, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < n_stages)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

static void	run_child_or_return(int (*pipes)[2], int n_stages,
			int n_pipes, t_env *env, t_ast **commands, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < n_stages)
	{
		if (pids[i] == 0)
		{
			dup_pipeline_ends(pipes, n_pipes, i, n_stages);
			close_all_pipes(pipes, n_pipes);
			run_child_command(commands[i], env);
			_exit(1);
		}
		i++;
	}
}

static int	get_last_status(pid_t *pids, int number_of_stages)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < number_of_stages)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (i == number_of_stages - 1)
				last_status = status_from_wait(status);
		}
		i++;
	}
	return (last_status);
}

int	exec_pipeline(t_ast *pipe_node, t_env *env)
{
	t_ast	**commands;
	pid_t	*pids;
	int		(*pipes)[2];
	int		n_stages;
	int		n_pipes;

	n_stages = count_commands(pipe_node);
	if (n_stages <= 0)
		return (0);
	if (n_stages == 1)
		return (exec_command(pipe_node, env));
	n_pipes = n_stages - 1;
	commands = malloc(sizeof(t_ast *) * n_stages);
	pids = malloc(sizeof(pid_t) * n_stages);
	pipes = malloc(sizeof(int[2]) * n_pipes);
	if (!commands || !pids || !pipes)
		return (1);
	collect_pipeline_stages(pipe_node, commands);
	if (create_pipes(pipes, n_pipes) != 0)
		return (1);
	if (spawn_pipeline_children(n_stages, pids) != 0)
		return (1);
	run_child_or_return(pipes, n_stages, n_pipes, env, commands, pids);
	close_all_pipes(pipes, n_pipes);
	return (get_last_status(pids, n_stages));
}
