/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:05:12 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 16:58:31 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
#include "../exec.h"
#include "env_utils/env_utils.h"

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha((unsigned char)s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	free_node_middle(t_env *prev, t_env *cur)
{
	prev->next = cur->next;
	free(cur->key);
	if (cur->value)
		free(cur->value);
	free(cur);
}

static void	clear_head_node(t_env *cur)
{
	free(cur->key);
	if (cur->value)
		free(cur->value);
	cur->key = NULL;
	cur->value = NULL;
}

static void	unset_one(char *key, t_env *env)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !key)
		return ;
	cur = env;
	prev = NULL;
	while (cur)
	{
		if (cur->key
			&& ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				free_node_middle(prev, cur);
			else
				clear_head_node(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	builtin_unset(char **argv, t_env *env)
{
	int	i;

	if (!argv || !argv[0] || !argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			unset_one(argv[i], env);
		else
		{
			write(2, "minishell: unset: `", 19);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		i++;
	}
	return (0);
}
