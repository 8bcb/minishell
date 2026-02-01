/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:45:10 by jziola            #+#    #+#             */
/*   Updated: 2026/02/01 13:19:24 by asia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_utils/env_utils.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*cur;

	count = 0;
	cur = env;
	while (cur)
	{
		if (is_exportable_key(cur->key))
			count++;
		cur = cur->next;
	}
	return (count);
}

static char	*create_env_string(t_env *cur)
{
	char	*tmp;
	char	*joined;

	if (cur->value)
	{
		tmp = ft_strjoin(cur->key, "=");
		if (!tmp)
			return (NULL);
		joined = ft_strjoin(tmp, cur->value);
		free(tmp);
	}
	else
		joined = ft_strdup(cur->key);
	return (joined);
}

static void	fill_envp_array(t_env *env, char **envp)
{
	t_env	*cur;
	int		i;
	char	*str;

	cur = env;
	i = 0;
	while (cur)
	{
		if (!is_exportable_key(cur->key))
		{
			cur = cur->next;
			continue ;
		}
		str = create_env_string(cur);
		if (!str)
		{
			envp[i] = NULL;
			return ;
		}
		envp[i++] = str;
		cur = cur->next;
	}
	envp[i] = NULL;
}

char	**env_to_envp(t_env *env)
{
	int		count;
	char	**envp;

	count = count_env_vars(env);
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	fill_envp_array(env, envp);
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
