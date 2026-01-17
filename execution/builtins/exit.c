/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:07:31 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 16:46:15 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"
#include "env_utils/env_utils.h"
#include <limits.h>
#include <errno.h>
#include <unistd.h>

static int	is_numeric_str(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	str_to_status(const char *s)
{
	long long	n;
	int			sign;

	n = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit((unsigned char)*s))
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	n *= sign;
	return ((unsigned char)n);
}

int	builtin_exit(char **argv, t_env *env)
{
	int	status;

	(void)env;
	write(2, "exit\n", 5);
	if (argv[1] && !is_numeric_str(argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": numeric argument required\n", 28);
		_exit(255);
	}
	if (argv[1] && argv[2])
	{
		print_cmd_error("exit", "too many arguments");
		return (1);
	}
	if (argv[1])
		status = str_to_status(argv[1]);
	else
		status = 0;
	_exit(status);
}
