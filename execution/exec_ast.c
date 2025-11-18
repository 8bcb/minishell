/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 06:54:16 by asia              #+#    #+#             */
/*   Updated: 2025/11/17 09:17:04 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int exec_ast(t_ast *node, t_env *env)
{
    if (!node)
        return 0;
    if (node -> type == NODE_COMMAND)
        return exec_command(node, env);
    if (node -> type == NODE_PIPE)
        return exec_pipeline(node, env);
    return 1;
}