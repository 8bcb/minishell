/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:15:57 by asia              #+#    #+#             */
/*   Updated: 2025/11/13 10:27:43 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec_redirection.h"
#include "../exec.h"
#include "../exec_external/exec_external.h"

static int apply_infile(const char *infile)
{
    int fd;

    if (!infile)
        return 0;
    fd = open(infile, O_RDONLY);
    if (fd < 0)
    {
        print_cmd_error(infile, strerror(errno));
        return 1;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        print_cmd_error(infile, strerror(errno));
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

static int apply_outfile(const char *outfile, int append)
{
    int fd;
    int flags;
    int append_flag;

    if (!outfile)
        return 0;
    if (append)
        append_flag = O_APPEND;
    else
        append_flag = O_TRUNC;
    flags = O_WRONLY | O_CREAT | append_flag;
    fd = open(outfile, flags, 0644);
    if (fd < 0)
    {
        print_cmd_error(outfile, strerror(errno));
        return 1;
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        print_cmd_error(outfile, strerror(errno));
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

int apply_redirection(const char *infile, const char *outfile, int append)
{
    if (apply_infile(infile) != 0)
        return 1;
    if (apply_outfile(outfile, append) != 0)
        return 1;
    return 0;
}

int save_stdio(int *saved_in, int *saved_out)
{
    if (saved_in)
    {
        *saved_in = dup(STDIN_FILENO);
        if (*saved_in < 0)
            return 1;
    }
    if (saved_out)
    {
        *saved_out = dup(STDOUT_FILENO);
        if (*saved_out < 0)
        {
            if (saved_in && *saved_in >= 0)
                close(*saved_in);
            return 1;
        }
    }
    return 0;
}

void restore_stdio(int saved_in, int saved_out)
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

char    *get_last_file(char **file)
{
    if (!file)
        return NULL;
    if (file[0])
        return file[0];
    return NULL;
}