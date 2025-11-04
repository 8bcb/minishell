/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:03:55 by asia              #+#    #+#             */
/*   Updated: 2025/11/04 08:47:08 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

extern char **environ;

int exec_external(char **argv, t_env *env)
{
    (void)env;
    int     child_process_status;
    char    *path;

    if (!argv || !argv[0] || !*argv[0])
        return 0;
    if (contains_slash(argv[0]))
    {
        child_process_status = spawn_execve(argv[0], argv);
        if (child_process_status == 127)
            print_cmd_error(argv[0], strerror(ENOENT));
        if (child_process_status == 126)
            print_cmd_error(argv[0], strerror(EACCES));
        return child_process_status;
    }
    path = resolve_in_path(argv[0]);
    if (!path)
    {
        print_cmd_error(argv[0], "command not found");
        return 127;
    }
    child_process_status = spawn_execve(path, argv);
    if (child_process_status == 126)
            print_cmd_error(argv[0], strerror(EACCES));
    free(path);
    return child_process_status;
}

int spawn_execve(const char *path, char **argv)
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
