/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:44:34 by jziola            #+#    #+#             */
/*   Updated: 2026/01/24 14:09:20 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:38:42 by asia              #+#    #+#             */
/*   Updated: 2025/12/02 08:53:42 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_utils/env_utils.h"

static void	process_env_entry(char *entry, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*node;

	key = NULL;
	value = NULL;
	split_key_value(entry, &key, &value);
	if (key)
	{
		node = env_node_new(key, value);
		if (node)
			env_add_back(env, node);
		free(key);
		if (value)
			free(value);
	}
}

t_env	*env_init(char **envp)
{
	int		i;
	t_env	*env;

	env = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		process_env_entry(envp[i], &env);
		i++;
	}
	return (env);
}

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (env->key && key
			&& ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}
