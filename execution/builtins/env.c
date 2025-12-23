/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:55:03 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:54:02 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"

int	builtin_env(char **argv, t_env *env)
{
	(void)argv;
	while (env)
	{
		if (env->key && env->value)
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
