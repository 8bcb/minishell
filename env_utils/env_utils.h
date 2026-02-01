/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:43:39 by jziola            #+#    #+#             */
/*   Updated: 2026/02/01 13:18:46 by asia             ###   ########.fr       */
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

void	assign_char(t_env_expand *var, int *single_quote, int *double_quote);
char	*get_env_key(t_env_expand *ex);
int		expand_last_status(t_env_expand *ex);
int		expand(t_env_expand *ex);
char	*expand_variables(char *rl, t_env *env);
int		is_exportable_key(const char *key);

#endif