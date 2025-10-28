/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 08:07:36 by asia              #+#    #+#             */
/*   Updated: 2025/10/28 08:15:28 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int exec_builtin(t_ast *cmd, t_env *env)
{
    char    *name;

    name = cmd -> argv[0];
    if (!name)
        return 0;

    if (ft_strcmp(name, "echo"))
    {
        exec_echo(cmd->argv);
    }
    return 1;
}