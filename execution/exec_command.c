/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:40:10 by asia              #+#    #+#             */
/*   Updated: 2025/11/06 09:42:56 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "./builtins.h"

int exec_command(t_ast *cmd, t_env *env)
{
    const t_builtin *builtin;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;
    builtin = builtin_lookup(cmd->argv[0]);
    if (builtin != NULL)
        return exec_builtin(cmd->argv, env);
    return exec_external(cmd->argv, env);
}
