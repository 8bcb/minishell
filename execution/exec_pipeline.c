/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:50:19 by jziola            #+#    #+#             */
/*   Updated: 2026/01/24 14:52:32 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exec_external/exec_external.h"

static void	free_pipeline(t_pipeline *pl)
{
	if (pl->stages)
		free(pl->stages);
	if (pl->pids)
		free(pl->pids);
	if (pl->pipes)
		free(pl->pipes);
}

static int	init_pipeline(t_ast *pipe_node, t_pipeline *pl)
{
	pl->n_stages = count_commands(pipe_node);
	if (pl->n_stages <= 0)
		return (1);
	pl->n_pipes = pl->n_stages - 1;
	pl->stages = malloc(sizeof (t_ast *) * pl->n_stages);
	pl->pids = malloc(sizeof (pid_t) * pl->n_stages);
	pl->pipes = NULL;
	if (!pl->stages || !pl->pids)
		return (1);
	if (pl->n_pipes > 0)
	{
		pl->pipes = malloc(sizeof (int [2]) * pl->n_pipes);
		if (!pl->pipes)
			return (1);
		if (create_pipes(pl->pipes, pl->n_pipes) != 0)
			return (1);
	}
	collect_pipeline_stages(pipe_node, pl->stages);
	return (0);
}

static int	fork_pipeline_child(t_pipeline *pl, int i, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (pl->n_pipes > 0)
		{
			dup_pipeline_ends(pl->pipes, pl->n_pipes, i, pl->n_stages);
			close_all_pipes(pl->pipes, pl->n_pipes);
		}
		run_child_command(pl->stages[i], env);
		_exit(1);
	}
	pl->pids[i] = pid;
	return (0);
}

static int	spawn_all_children(t_pipeline *pl, t_env *env)
{
	int	i;

	i = 0;
	while (i < pl->n_stages)
	{
		if (fork_pipeline_child(pl, i, env) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_pipeline(t_ast *pipe_node, t_env *env)
{
	t_pipeline			pl;
	int					status;

	if (!pipe_node)
		return (0);
	pl.stages = NULL;
	pl.pids = NULL;
	pl.pipes = NULL;
	if (init_pipeline(pipe_node, &pl) != 0)
	{
		free_pipeline(&pl);
		return (1);
	}
	if (spawn_all_children(&pl, env) != 0)
	{
		if (pl.n_pipes > 0)
			close_all_pipes(pl.pipes, pl.n_pipes);
		free_pipeline(&pl);
		return (1);
	}
	if (pl.n_pipes > 0)
		close_all_pipes(pl.pipes, pl.n_pipes);
	status = get_last_status(pl.pids, pl.n_stages);
	free_pipeline(&pl);
	return (status);
}
