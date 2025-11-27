/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:16:06 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 08:26:19 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_EXTERNAL_H
#  define EXEC_EXTERNAL_H

#include "../exec.h"

typedef struct s_env t_env;

int     exec_external(t_ast *cmd, t_env *env);
char    *resolve_in_path(char *command);
int spawn_execve_with_redirs(const char *path, t_ast *cmd, char **envp);
void    exec_external_child(t_ast *cmd, t_env *env);

// exec_external_utils.c
void        free_split(char **split_array);
char        *join_path(const char *dir, const char *command);
int         status_from_wait(int status);
int         contains_slash(const char *str);

#endif