/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:40:10 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 08:15:25 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "./builtins/builtins.h"
#include "./redirection/exec_redirection.h"
#include "./exec_external/exec_external.h"

int exec_command(t_ast *cmd, t_env *env)
{
    const t_builtin *builtin;
    int             saved_in;
    int             saved_out;
    int             status;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;
    builtin = builtin_lookup(cmd->argv[0]);
    if (builtin != NULL)
    {
        if (save_stdio(&saved_in, &saved_out) != 0)
            return 1;
        if (apply_redirection(get_last_file(cmd->infile), get_last_file(cmd->outfile), cmd->append, cmd->heredoc_tmp) != 0)
        {
            restore_stdio(saved_in, saved_out);
            return 1;
        }
        status = exec_builtin(cmd->argv, env);
        restore_stdio(saved_in, saved_out);
        return status;
    }
    return exec_external(cmd, env);
}

void    run_child_command(t_ast *cmd, t_env *env)
{
    const t_builtin *builtin;
    int             status;

    if (apply_redirection(get_last_file(cmd->infile), get_last_file(cmd->outfile), cmd->append, cmd->heredoc_tmp) != 0)
        _exit(1);
    builtin = builtin_lookup(cmd->argv[0]);
    if (builtin != NULL)
    {
        status = exec_builtin(cmd->argv, env);
        _exit(status);
    }
    exec_external_child(cmd, env);
}
