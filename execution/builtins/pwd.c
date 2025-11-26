/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:17 by asia              #+#    #+#             */
/*   Updated: 2025/11/26 09:54:29 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include <unistd.h>
#include "libft.h"

int builtin_pwd(char **argv, t_env *env)
{
    char    *cwd;

    (void)argv;
    (void)env;
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return 1;
    write(1, cwd, ft_strlen(cwd));
    write(1, "\n", 1);
    free(cwd);
    retun 0;
}