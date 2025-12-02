/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:04:18 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:04:27 by asia             ###   ########.fr       */
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