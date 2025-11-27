/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:54:21 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 07:54:48 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

void    print_cmd_error(const char *command, const char *message)
{
    if (!command)
        command = "";
    if (!message)
        message = "";
    write(2, "minishell: ", 11);
    write(2, command, ft_strlen(command));
    write(2, ": ", 2);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
}