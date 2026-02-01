/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:55:03 by asia              #+#    #+#             */
/*   Updated: 2026/02/01 13:22:27 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"
#include "../../env_utils/env_utils.h"

int	builtin_env(char **argv, t_env *env)
{
	if (argv && argv[1])
	{
		print_cmd_error("env", "too many arguments");
		return (1);
	}
	while (env)
	{
		if (is_exportable_key(env->key) && env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
