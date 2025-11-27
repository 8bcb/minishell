/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 07:54:28 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 07:53:24 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "libft.h"
#include <unistd.h>

typedef struct s_env t_env;

typedef int (*t_builtin_fn)(char **argv, t_env *env);

typedef struct s_builtin {
    const char      *name;
    t_builtin_fn    fn;
    int             must_run_in_parent;
} t_builtin;

const t_builtin     *builtin_lookup(const char *name);
int                 exec_builtin(char **argv, t_env *env);

int				builtin_echo(char **argv, t_env *env);
int				builtin_pwd(char **argv, t_env *env);
int				builtin_env(char **argv, t_env *env);
int				builtin_cd(char **argv, t_env *env);
int				builtin_export(char **argv, t_env *env);
int				builtin_unset(char **argv, t_env *env);
int				builtin_exit(char **argv, t_env *env);

int             is_new_line(char *str);

#endif