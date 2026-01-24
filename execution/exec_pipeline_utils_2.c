/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:04:18 by asia              #+#    #+#             */
/*   Updated: 2026/01/24 14:53:11 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "exec_external/exec_external.h"

void	close_all_pipes(int (*pipes)[2], int number_of_pipes)
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

int	get_last_status(pid_t *pids, int n_stages)
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
