/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:07:36 by asia              #+#    #+#             */
/*   Updated: 2025/10/30 08:48:27 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int exec_builtin(t_ast *cmd, t_env *env)
{
    char    *name;

    name = cmd -> argv[0];
    if (!name)
        return 0;
    (void)env;
    if (ft_strncmp(name, "echo", sizeof("echo")) == 0)
    {
        return builtin_echo(cmd->argv);
    }
    return 1;
}