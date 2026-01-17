/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 06:49:09 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 16:46:15 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"
#include "env_utils/env_utils.h"
#include <unistd.h>
#include <errno.h>
#include <limits.h>

static void	update_pwd_vars(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = env_get(env, "PWD");
	if (oldpwd)
	{
		env_set(&env, "OLDPWD", oldpwd);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		env_set(&env, "PWD", cwd);
	}
}

int	builtin_cd(char **argv, t_env *env)
{
	const char	*path;

	if (!argv || !argv[0])
		return (0);
	if (!argv[1] || argv[2])
	{
		print_cmd_error("cd", "usage: cd <path>");
		return (1);
	}
	path = argv[1];
	if (chdir(path) != 0)
	{
		print_cmd_error("cd", strerror(errno));
		return (1);
	}
	update_pwd_vars(env);
	return (0);
}
