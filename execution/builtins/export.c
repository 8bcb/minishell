/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 06:59:57 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:52:24 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"
#include "env_utils.h"

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	export_one(char *arg, t_env *env)
{
	char	*eq;
	char	*key;
	char	*value;
	t_env	*tmp;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		key = arg;
		value = eq + 1;
	}
	else
	{
		key = arg;
		value = NULL;
	}
	if (!is_valid_identifier(key))
	{
		write(2, "minishell: export: `", 21);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		if (eq)
			*eq = '=';
		return (1);
	}
	tmp = env;
	if (env_set(&tmp, key, value) != 0)
	{
		if (eq)
			*eq = '=';
		return (1);
	}
	if (eq)
		*eq = '=';
	return (0);
}

int	builtin_export(char **argv, t_env *env)
{
	int	i;
	int	status;

	if (!argv || !argv[0])
		return (0);
	if (!argv[1])
		return (builtin_env(argv, env));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (export_one(argv[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}
