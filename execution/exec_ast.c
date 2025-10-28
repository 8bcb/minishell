/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 06:54:16 by asia              #+#    #+#             */
/*   Updated: 2025/10/28 07:11:00 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int exec_ast(t_ast *node, t_env *env)
{
    if (!node)
    {
        return 0;
    }

    if (node -> type == NODE_COMMAND)
    {
        return exec_command(node, env);
    }
    else if (node -> type == NODE_PIPE)
    {
        return exec_pipe(node, env);
    }
    else if (node -> type == NODE_REDIR_IN || node -> type == NODE_REDIR_OUT || node -> type == NODE_REDIR_APPEND)
    {
        return exec_redirection(node, env);
    }
    else if (node -> type == NODE_HEREDOC)
    {
        return exec_heredoc(node, env);
    }
    return 1;
}