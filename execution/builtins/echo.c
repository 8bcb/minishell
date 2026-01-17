/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 07:59:23 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 16:53:01 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"

int	builtin_echo(char **argv, t_env *env)
{
	int	i;
	int	print_newline;
	int	str_len;

	(void)env;
	i = 1;
	print_newline = 1;
	while (argv[i] && is_new_line(argv[i]))
	{
		print_newline = 0;
		i++;
	}
	while (argv[i])
	{
		str_len = ft_strlen(argv[i]);
		if (str_len)
			write(1, argv[i], str_len);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (print_newline)
		write(1, "\n", 1);
	return (0);
}

int	is_new_line(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	if (str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
