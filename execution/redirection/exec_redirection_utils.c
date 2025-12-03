/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:10:37 by asia              #+#    #+#             */
/*   Updated: 2025/12/03 08:38:54 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"

extern volatile sig_atomic_t g_sig;

int	open_heredoc_fd(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (!delimiter)
		return (-1);
	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		if (g_sig == SIGINT)
			break ;
		line = readline("> ");
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
	if (g_sig == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}

int  open_infile(char *infile)
{
    int fd;

    fd = open(infile, O_RDONLY);
    if (fd < 0)
        print_cmd_error(infile, strerror(errno));
    return (fd);
}

int  open_outfile(char *outfile, int append)
{
    int flags;
    int fd;

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

char    *get_last_file(char **file)
{
    if (!file)
        return (NULL);
    if (file[0])
        return (file[0]);
    return (NULL);
}