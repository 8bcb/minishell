/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 06:49:09 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 07:56:35 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"

int builtin_cd(char **argv, t_env *env)
{
    int    res;
    (void)env;

    if (!argv[1] || argv[2])
        return (print_cmd_error("cd", "usage: cd <path>"), 1);
    res = chdir(argv[1]);
    if (res != 0)
        return (print_cmd_error("cd", strerror(errno)), 1);
    return 0;
}