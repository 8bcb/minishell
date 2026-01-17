/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:07:36 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 16:55:25 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/exec.h"
#include "./builtins.h"

static const t_builtin	*get_builtins(void)
{
	static const t_builtin	builtins[] = {
	{"pwd", &builtin_pwd, 0},
	{"env", &builtin_env, 0},
	{"cd", &builtin_cd, 1},
	{"export", &builtin_export, 1},
	{"unset", &builtin_unset, 1},
	{"exit", &builtin_exit, 1},
	{NULL, NULL, 0}
	};

	return (builtins);
}

int	exec_builtin(char **argv, t_env *env)
{
	const t_builtin	*builtin;

	if (!argv || !argv[0])
		return (0);
	builtin = builtin_lookup(argv[0]);
	if (!builtin || !builtin->fn)
		return (1);
	return (builtin->fn(argv, env));
}

static int	builtin_name_match(const char *builtin_name, const char *name)
{
	if (ft_strncmp(builtin_name, name, ft_strlen(name) + 1) == 0
		&& ft_strlen(name) == ft_strlen(builtin_name))
		return (1);
	return (0);
}

const t_builtin	*builtin_lookup(const char *name)
{
	const t_builtin	*builtins;
	int				i;

	if (!name || !*name)
		return (NULL);
	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (builtin_name_match(builtins[i].name, name))
			return (&builtins[i]);
		i++;
	}
	return (NULL);
}
