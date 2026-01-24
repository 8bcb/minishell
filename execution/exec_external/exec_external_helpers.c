/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:03:55 by asia              #+#    #+#             */
/*   Updated: 2026/01/24 17:21:47 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"
#include "./exec_external.h"
#include <errno.h>
#include <string.h>

int	exec_with_slash(t_ast *cmd, char **envp)
{
	int	status;

	status = spawn_execve_with_redirs(cmd->argv[0], cmd, envp);
	if (status == 127)
		print_cmd_error(cmd->argv[0], strerror(ENOENT));
	if (status == 126)
		print_cmd_error(cmd->argv[0], strerror(EACCES));
	return (status);
}

int	exec_from_path(t_ast *cmd, char **envp, t_env *env)
{
	char	*path;
	int		status;

	path = resolve_in_path(cmd->argv[0], env);
	if (!path)
	{
		print_cmd_error(cmd->argv[0], "command not found");
		return (127);
	}
	status = spawn_execve_with_redirs(path, cmd, envp);
	if (status == 127)
		print_cmd_error(cmd->argv[0], strerror(ENOENT));
	if (status == 126)
		print_cmd_error(cmd->argv[0], strerror(EACCES));
	free(path);
	return (status);
}
