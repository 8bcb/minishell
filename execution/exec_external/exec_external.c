/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:03:55 by asia              #+#    #+#             */
/*   Updated: 2026/01/31 12:46:03 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"
#include "../redirection/exec_redirection.h"
#include "env_utils/env_utils.h"
#include "./exec_external.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static void	exec_child_process(const char *path, t_ast *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_redirection(cmd) != 0)
		_exit(1);
	execve(path, cmd->argv, envp);
	if (errno == ENOENT)
		_exit(127);
	if (errno == EACCES || errno == ENOTDIR || errno == EISDIR)
		_exit(126);
	_exit(126);
}

int	spawn_execve_with_redirs(const char *path, t_ast *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	pid = fork();
	if (pid < 0)
	{
		print_cmd_error(cmd->argv[0], strerror(errno));
		return (1);
	}
	if (pid == 0)
		exec_child_process(path, cmd, envp);
	waitpid(pid, &status, 0);
	return (status_from_wait(status));
}

static void	exec_with_path(char *path, t_ast *cmd, char **envp)
{
	execve(path, cmd->argv, envp);
	if (errno == ENOENT)
		_exit(127);
	if (errno == EACCES || errno == ENOTDIR || errno == EISDIR)
		_exit(126);
	_exit(126);
}

void	exec_external_child(t_ast *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	envp = env_to_envp(env);
	if (contains_slash(cmd->argv[0]))
		exec_with_path(cmd->argv[0], cmd, envp);
	path = resolve_in_path(cmd->argv[0], env);
	if (!path)
	{
		print_cmd_error(cmd->argv[0], "command not found");
		_exit(127);
	}
	exec_with_path(path, cmd, envp);
}

int	exec_external(t_ast *cmd, t_env *env)
{
	int		status;
	char	**envp;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	envp = env_to_envp(env);
	if (!envp)
		return (1);
	if (contains_slash(cmd->argv[0]))
		status = exec_with_slash(cmd, envp);
	else
		status = exec_from_path(cmd, envp, env);
	free_envp_array(envp);
	return (status);
}
