/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:40:58 by asia              #+#    #+#             */
/*   Updated: 2026/02/01 13:40:59 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

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

static int	apply_heredoc(t_ast *cmd)
{
	int	fd;

	if (!cmd->heredoc || cmd->heredoc_fd < 0)
		return (0);
	fd = cmd->heredoc_fd;
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		print_cmd_error("heredoc", strerror(errno));
		close(fd);
		cmd->heredoc_fd = -1;
		return (1);
	}
	close(fd);
	cmd->heredoc_fd = -1;
	return (0);
}

int	apply_all_infiles(char **infiles)
{
	int	fd;
	int	i;

	if (!infiles)
		return (0);
	i = 0;
	while (infiles[i])
	{
		fd = open_infile(infiles[i]);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			print_cmd_error(infiles[i], strerror(errno));
			close(fd);
			return (1);
		}
		close(fd);
		i++;
	}
	return (0);
}

int	apply_all_outfiles(char **outfiles, int *out_append)
{
	int	fd;
	int	i;
	int	append;

	if (!outfiles)
		return (0);
	i = 0;
	while (outfiles[i])
	{
		append = 0;
		if (out_append)
			append = out_append[i];
		fd = open_outfile(outfiles[i], append);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			print_cmd_error(outfiles[i], strerror(errno));
			close(fd);
			return (1);
		}
		close(fd);
		i++;
	}
	return (0);
}

int	apply_redirection(t_ast *cmd)
{
	if (!cmd)
		return (0);
	if (apply_heredoc(cmd) != 0)
		return (1);
	if (!cmd->heredoc && apply_all_infiles(cmd->infile) != 0)
		return (1);
	if (apply_all_outfiles(cmd->outfile, cmd->out_append) != 0)
		return (1);
	return (0);
}
