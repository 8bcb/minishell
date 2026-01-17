/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:44:12 by jziola            #+#    #+#             */
/*   Updated: 2026/01/17 16:46:15 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:38:42 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:53:42 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_utils/env_utils.h"

t_env	*env_node_new(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	if (value && !node->value)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*cur;

	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
}

void	split_key_value(const char *entry, char **key, char **value)
{
	char	*eq;
	size_t	key_len;

	eq = ft_strchr(entry, '=');
	if (!eq)
	{
		*key = ft_strdup(entry);
		*value = NULL;
		return ;
	}
	key_len = (size_t)(eq - entry);
	*key = (char *)malloc(key_len + 1);
	if (!*key)
	{
		*value = NULL;
		return ;
	}
	ft_memcpy(*key, entry, key_len);
	(*key)[key_len] = '\0';
	*value = ft_strdup(eq + 1);
	if (!*value)
	{
		free(*key);
		*key = NULL;
	}
}
