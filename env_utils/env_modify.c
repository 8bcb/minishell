/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:38:42 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 16:50:33 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_utils.h"

int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*cur;

	if (!env || !key || !*key)
		return (1);
	cur = *env;
	while (cur)
	{
		if (cur->key
			&& ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			free(cur->value);
			if (value)
				cur->value = ft_strdup(value);
			else
				cur->value = NULL;
			return (0);
		}
		cur = cur->next;
	}
	cur = env_node_new(key, value);
	if (!cur)
		return (1);
	env_add_back(env, cur);
	return (0);
}

static void	free_env_node(t_env **env, t_env *cur, t_env *prev)
{
	if (prev)
		prev->next = cur->next;
	else
		*env = cur->next;
	free(cur->key);
	if (cur->value)
		free(cur->value);
	free(cur);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !*env || !key)
		return (0);
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (cur->key
			&& ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			free_env_node(env, cur, prev);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
