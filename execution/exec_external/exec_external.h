/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:16:06 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 17:09:42 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_EXTERNAL_H
# define EXEC_EXTERNAL_H

# include "../exec.h"

typedef struct s_env	t_env;

int		exec_external(t_ast *cmd, t_env *env);
char	*resolve_in_path(char *command);
int		spawn_execve_with_redirs(const char *path, t_ast *cmd, char **envp);
void	exec_external_child(t_ast *cmd, t_env *env);
int		exec_with_slash(t_ast *cmd, char **envp);
int		exec_from_path(t_ast *cmd, char **envp);

void	free_split(char **split_array);
char	*join_path(const char *dir, const char *command);
int		status_from_wait(int status);
int		contains_slash(const char *str);

#endif