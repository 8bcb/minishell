/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:57 by asia              #+#    #+#             */
/*   Updated: 2025/12/03 08:41:02 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

extern volatile sig_atomic_t g_sig;

int save_stdio(int *saved_in, int *saved_out)
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

void    restore_stdio(int saved_in, int saved_out)
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

int apply_redirection(t_ast *cmd)
{
    int     fd;
    char    *infile;
    char    *outfile;

    if (!cmd)
        return (0);
    infile = get_last_file(cmd->infile);
    outfile = get_last_file(cmd->outfile);
	if (cmd->heredoc && cmd->heredoc_fd >= 0)
    {
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
        fd = open_outfile(outfile, cmd->append);
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

static int	preprocess_heredoc_for_cmd(t_ast *cmd)
{
	int	fd;

	if (!cmd || !cmd->heredoc_tmp)
		return (0);
	fd = open_heredoc_fd(cmd->heredoc_tmp);
	if (fd < 0)
	{
		if (g_sig == SIGINT)
			return (130);
		return (1);
	}
	cmd->heredoc_fd = fd;
	return (0);
}

int	preprocess_heredocs(t_ast *node)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (preprocess_heredoc_for_cmd(node));
	if (node->type == NODE_PIPE)
	{
		status = preprocess_heredocs(node->left);
		if (status != 0)
			return (status);
		return (preprocess_heredocs(node->right));
	}
	return (0);
}