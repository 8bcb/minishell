/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:43:39 by jziola            #+#    #+#             */
/*   Updated: 2026/01/24 17:19:36 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:28:27 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:29:23 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "../minishell.h"

typedef struct s_env_expand
{
	int		i;
	int		j;
	char	*rl;
	char	*res;
	t_env	*env;
}	t_env_expand;

t_env	*env_node_new(const char *key, const char *value);
void	env_add_back(t_env **env, t_env *new_node);
void	split_key_value(const char *entry, char **key, char **value);

t_env	*env_init(char **envp);
char	*env_get(t_env *env, const char *key);

int		env_set(t_env **env, const char *key, const char *value);
int		env_unset(t_env **env, const char *key);

char	**env_to_envp(t_env *env);
void	free_envp_array(char **envp);

void	free_env_list(t_env *env);
char	*search_env_list(t_env *env, char *var_name, int len);

#endif