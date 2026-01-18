/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:57 by asia              #+#    #+#             */
/*   Updated: 2026/01/18 13:13:14 by jziola           ###   ########.fr       */
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

static int	apply_infile(char *infile)
{
	int	fd;

	if (!infile)
		return (0);
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
	return (0);
}

static int	apply_outfile(char *outfile, int append)
{
	int	fd;

	if (!outfile)
		return (0);
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
	return (0);
}

int	apply_redirection(t_ast *cmd)
{
	char	*infile;
	char	*outfile;

	if (!cmd)
		return (0);
	infile = get_last_file(cmd->infile);
	outfile = get_last_file(cmd->outfile);
	if (apply_heredoc(cmd) != 0)
		return (1);
	if (!cmd->heredoc && apply_infile(infile) != 0)
		return (1);
	if (apply_outfile(outfile, cmd->append) != 0)
		return (1);
	return (0);
}
