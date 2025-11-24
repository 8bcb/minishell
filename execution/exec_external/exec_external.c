/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:03:55 by asia              #+#    #+#             */
/*   Updated: 2025/11/24 09:04:24 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"
#include "../redirection/exec_redirection.h"
#include "./exec_external.h"

extern char **environ;

int     spawn_execve_with_redirs(const char *path, char **argv, const char *infile, 
    const char *outfile, int append)
{
    pid_t   pid;
    int     status;
    
    pid = fork();
    if (pid < 0)
    {
        print_cmd_error(argv[0], strerror(errno));
        return 1;
    }
    if (pid == 0)
    {
        if (apply_redirection(infile, outfile, append) != 0)
            _exit(1);
        execve(path, argv, environ);
        if (errno == ENOENT)
            _exit(127);
        if (errno == EACCES || errno == ENOTDIR || errno == EISDIR)
            _exit(126);
        _exit(126);
    }
    waitpid(pid, &status, 0);
    return status_from_wait(status);
}

void    exec_external_child(t_ast *cmd, t_env *env)
{
    char *path;
    
    (void)env;
    if (contains_slash(cmd->argv[0]))
    {
        execve(cmd->argv[0], cmd->argv, environ);
        if (errno == ENOENT)
            _exit(127);
        if (errno == EACCES || errno == ENOTDIR || errno == EISDIR)
            _exit(126);
        _exit(126);
    }
    path = resolve_in_path(cmd->argv[0]);
    if (!path)
    {
        print_cmd_error(cmd->argv[0], "command not found");
        _exit(127);
    }
    execve(path, cmd->argv, environ);
    if (errno == ENOENT)
        _exit(127);
    if (errno == EACCES || errno == ENOTDIR || errno == EISDIR)
        _exit(126);
    _exit(126);
}

int exec_external(t_ast *cmd, t_env *env)
{
    (void)env;
    int     child_process_status;
    char    *path;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;
    if (contains_slash(cmd->argv[0]))
    {
        child_process_status = spawn_execve_with_redirs(cmd->argv[0], cmd->argv, get_last_file(cmd->infile), 
        get_last_file(cmd->outfile), cmd->append);
        if (child_process_status == 127)
            print_cmd_error(cmd->argv[0], strerror(ENOENT));
        if (child_process_status == 126)
            print_cmd_error(cmd->argv[0], strerror(EACCES));
        return child_process_status;
    }
    path = resolve_in_path(cmd->argv[0]);
    if (!path)
    {
        print_cmd_error(cmd->argv[0], "command not found");
        return 127;
    }
    child_process_status = spawn_execve_with_redirs(path, cmd->argv, get_last_file(cmd->infile), 
        get_last_file(cmd->outfile), cmd->append);
    if (child_process_status == 127)
            print_cmd_error(cmd->argv[0], strerror(ENOENT));
    if (child_process_status == 126)
            print_cmd_error(cmd->argv[0], strerror(EACCES));
    free(path);
    return child_process_status;
}

char    *resolve_in_path(char *command)
{
    const char  *path;
    char        **potential_paths;
    int         i;
    char        *candidate;

    path = getenv("PATH");
    if (!path || !*path)
        return NULL;
    potential_paths = ft_split(path, ':');
    if (!potential_paths)
        return NULL;
    i = 0;
    while (potential_paths[i])
    {
        candidate = join_path(potential_paths[i], command);
        if (!candidate)
        {
            free_split(potential_paths);
            return NULL;
        }
        if (candidate)
        {
            if (access(candidate, X_OK) == 0)
            {
                free_split(potential_paths);
                return candidate;
            }
            free(candidate);
        }
        i++;
    }
    free_split(potential_paths);
    return NULL;
}
