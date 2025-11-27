/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:07:31 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 07:56:59 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"

static int is_numeric(const char *s)
{
    int i;

    if (!s || !*s)
        return 0;
    i = 0;
    if (s[i] == '+' || s[i] == '-')
        i++;
    if (!s[i])
        return 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return 0;
        i++;
    }
    return 1;
}

int builtin_exit(char **argv, t_env *env)
{
    int status;
    (void)env;
    if (argv[1] && argv[2])
        return (print_cmd_error("exit", "too many arguments\n"), 1);
    if (argv[1])
    {
        if (!is_numeric(argv[1]))
            return (print_cmd_error("exit", "numeric argument required"), 1);
        status = (unsigned char)ft_atoi(argv[1]);
    }
    else
        status = 0;
    exit(status);
}