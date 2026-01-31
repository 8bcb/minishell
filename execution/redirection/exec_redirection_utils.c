/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:10:37 by asia              #+#    #+#             */
/*   Updated: 2026/01/31 12:22:11 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include "../../signals.h"

static int	process_heredoc_line(char *line, const char *delim, int write_fd)
{
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
	{
		free(line);
		return (1);
	}
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
	return (0);
}

int	open_heredoc_fd(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (!delimiter || pipe(pipefd) < 0)
		return (-1);
	g_sig = 0;
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT || !line)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(line, delimiter, pipefd[1]))
			break ;
	}
	close(pipefd[1]);
	if (g_sig == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}

int	open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		print_cmd_error(infile, strerror(errno));
	return (fd);
}

int	open_outfile(char *outfile, int append)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
		print_cmd_error(outfile, strerror(errno));
	return (fd);
}

char	*get_last_file(char **file)
{
	int	i;

	if (!file)
		return (NULL);
	i = 0;
	while (file[i])
		i++;
	if (i == 0)
		return (NULL);
	return (file[i - 1]);
}
