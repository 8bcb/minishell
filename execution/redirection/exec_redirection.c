/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:57 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:18:02 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include "libft.h"

extern FILE *rl_outstream;

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

void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in >= 0)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out >= 0)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

int	apply_redirection(char *infile,
						char *outfile,
						int append,
						char *heredoc_delim)
{
	int	fd;

	if (heredoc_delim)
	{
		fd = open_heredoc_fd(heredoc_delim);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			print_cmd_error("heredoc", strerror(errno));
			close(fd);
			return (1);
		}
		close(fd);
	}
	else if (infile)
	{
		fd = open_infile(infile);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			print_cmd_error(infile, strerror(errno));
			close(fd);
			return (1);
		}
		close(fd);
	}
	if (outfile)
	{
		fd = open_outfile(outfile, append);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			print_cmd_error(outfile, strerror(errno));
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}