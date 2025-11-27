/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:07:36 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 06:50:35 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/exec.h"
#include "./builtins.h"

static const t_builtin g_builtins[] = {
	{ "pwd",   &builtin_pwd,   0 },
	{ "env",   &builtin_env,   0 },
	{ "cd",    &builtin_cd,    1 },
	{ "export",&builtin_export,1 },
	{ "unset", &builtin_unset, 1 },
	{ "exit",  &builtin_exit,  1 },
	{ NULL,    NULL,           0 }
};

int exec_builtin(char **argv, t_env *env)
{
    const t_builtin     *builtin;

    if (!argv || !argv[0])
        return 0;
    builtin = builtin_lookup(argv[0]);
    if (!builtin || !builtin->fn)
        return 1;
    return (builtin->fn(argv, env));
}

const t_builtin     *builtin_lookup(const char *name)
{
    int i;

    if (!name || !*name)
        return NULL;
    i = 0;
    while (g_builtins[i].name)
    {
        if (ft_strncmp(g_builtins[i].name, name, ft_strlen(name) + 1) == 0 && ft_strlen(name) == ft_strlen(g_builtins[i].name))
            return &g_builtins[i];
        i++;
    }
    return NULL;
}
