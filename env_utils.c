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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:00:00 by asia              #+#    #+#             */
/*   Updated: 2025/11/27 12:00:00 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_utils.h"

static t_env	*env_node_new(const char *key, const char *value)
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

static void	env_add_back(t_env **env, t_env *new_node)
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

static void	split_key_value(const char *entry, char **key, char **value)
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

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*node;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		split_key_value(envp[i], &key, &value);
		if (key)
		{
			node = env_node_new(key, value);
			if (!node)
			{
				free(key);
				if (value)
					free(value);
				return (env);
			}
			env_add_back(&env, node);
			free(key);
			if (value)
				free(value);
		}
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
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			if (cur->value)
				free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

char	**env_to_envp(t_env *env)
{
	int		count;
	t_env	*cur;
	char	**envp;
	char	*joined;
	char	*tmp;

	count = 0;
	cur = env;
	while (cur)
	{
		if (cur->key)
			count++;
		cur = cur->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	cur = env;
	count = 0;
	while (cur)
	{
		if (!cur->key)
		{
			cur = cur->next;
			continue ;
		}
		if (cur->value)
		{
			tmp = ft_strjoin(cur->key, "=");
			if (!tmp)
				return (envp);
			joined = ft_strjoin(tmp, cur->value);
			free(tmp);
		}
		else
			joined = ft_strdup(cur->key);
		if (!joined)
			return (envp);
		envp[count++] = joined;
		cur = cur->next;
	}
	envp[count] = NULL;
	return (envp);
}

void	free_envp_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
