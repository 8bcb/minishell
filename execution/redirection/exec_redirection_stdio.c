/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_stdio.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:10:37 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 17:36:18 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include <unistd.h>

int	save_stdio(int *saved_in, int *saved_out)
{
	*saved_in = dup(STDIN_FILENO);
	if (*saved_in < 0)
		return (-1);
	*saved_out = dup(STDOUT_FILENO);
	if (*saved_out < 0)
	{
		close(*saved_in);
		*saved_in = -1;
		return (-1);
	}
	return (0);
}
