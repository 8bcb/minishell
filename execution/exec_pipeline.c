/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:00:00 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 10:15:12 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "./exec_external/exec_external.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
** close_all_pipes:
**   Close every pipe fd in parent or child.
*/
static void	close_all_pipes(int (*pipes)[2], int number_of_pipes)
{
	int	i;

	if (!pipes || number_of_pipes <= 0)
		return ;
	i = 0;
	while (i < number_of_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

/*
** get_last_status:
**   Waits for all pids; returns the exit status of the last stage
**   (standard shell semantics).
*/
static int	get_last_status(pid_t *pids, int n_stages)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < n_stages)
	{
		if (waitpid(pids[i], &status, 0) > 0)
			last_status = status_from_wait(status);
		i++;
	}
	return (last_status);
}

/*
** exec_pipeline:
**   Execute a pipeline represented by a NODE_PIPE tree.
**   - Flatten tree into stages[]
**   - Create pipes
**   - Fork n_stages children, wiring stdin/stdout via dup2
**   - In each child: apply pipes, then run_child_command(stages[i], env)
**   - Parent: close all pipes, wait all children, return status of last stage
*/
int	exec_pipeline(t_ast *pipe_node, t_env *env)
{
	int		n_stages;
	int		n_pipes;
	t_ast	**stages;
	int		(*pipes)[2];
	pid_t	*pids;
	int		i;
	pid_t	pid;

	if (!pipe_node)
		return (0);
	n_stages = count_commands(pipe_node);
	if (n_stages <= 0)
		return (0);
	n_pipes = n_stages - 1;
	stages = (t_ast **)malloc(sizeof(t_ast *) * n_stages);
	pids = (pid_t *)malloc(sizeof(pid_t) * n_stages);
	pipes = NULL;
	if (!stages || !pids)
		return (1);
	if (n_pipes > 0)
	{
		pipes = (int (*)[2])malloc(sizeof(int[2]) * n_pipes);
		if (!pipes)
			return (1);
		if (create_pipes(pipes, n_pipes) != 0)
			return (1);
	}
	collect_pipeline_stages(pipe_node, stages);
	i = 0;
	while (i < n_stages)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			/* child: wire stdin/stdout to pipes, then exec command */
			if (n_pipes > 0)
			{
				dup_pipeline_ends(pipes, n_pipes, i, n_stages);
				close_all_pipes(pipes, n_pipes);
			}
			run_child_command(stages[i], env);
			_exit(1);
		}
		pids[i] = pid;
		i++;
	}
	if (n_pipes > 0)
		close_all_pipes(pipes, n_pipes);
	i = get_last_status(pids, n_stages);
	free(stages);
	free(pids);
	if (pipes)
		free(pipes);
	return (i);
}
