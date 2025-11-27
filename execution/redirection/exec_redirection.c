/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:57 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 10:01:31 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include "libft.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

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

char	*get_last_file(char **file)
{
	if (!file)
		return (NULL);
	if (file[0])
		return (file[0]);
	return (NULL);
}

static char	*heredoc_read_line(void)
{
	char	buf[1024];
	int		i;
	char	c;
	ssize_t	nread;

	i = 0;
	while (1)
	{
		nread = read(STDIN_FILENO, &c, 1);
		if (nread <= 0)
		{
			if (i == 0)
				return (NULL);
			break ;
		}
		if (c == '\n')
			break ;
		if (i < (int)(sizeof(buf) - 1))
		{
			buf[i] = c;
			i++;
		}
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}

static int	open_outfile(char *outfile, int append)
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

static int	open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		print_cmd_error(infile, strerror(errno));
	return (fd);
}

static int	open_heredoc_fd(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (!delimiter)
		return (-1);
	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		/* prompt on stderr so it always shows, even with pipes/redirs */
		write(2, "> ", 2);
		line = heredoc_read_line();
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter,
				ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

/*
** heredoc_delim != NULL  -> stdin from heredoc
** else if infile != NULL -> stdin from infile
** outfile != NULL        -> stdout to > or >>
*/
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