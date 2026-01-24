/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:04:18 by asia              #+#    #+#             */
/*   Updated: 2026/01/24 13:50:55 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

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
