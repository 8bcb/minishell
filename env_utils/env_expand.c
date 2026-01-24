/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:52 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/24 14:32:17 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "env_utils.h"

void	assign_char(t_env_expand *var, int *single_quote)
{
	if (var->rl[var->i] == 39)
	{
		if (*single_quote == 0)
			*single_quote = 1;
		else
			*single_quote = 0;
	}
	var->res[(var->j)++] = var->rl[(var->i)++];
}

char	*get_env_key(t_env_expand *ex, int *len)
{
	int		k;
	char	*var_key;

	k = ex->i + 1;
	while (ex->rl[k] && (ft_isalnum(ex->rl[k]) || ex->rl[k] == '_'))
	{
		(*len)++;
		k++;
	}
	if (*len == 0)
		return (NULL);
	var_key = ft_substr(ex->rl, ex->i + 1, *len);
	if (!var_key)
		return (NULL);
	ex->i += *len + 1;
	return (var_key);
}

char	*search_env_list(t_env *env, char *var_name, int len)
{
	t_env	*tmp;
	char	*var_value;

	tmp = env;
	var_value = NULL;
	while (tmp)
	{
		if (ft_strncmp(var_name, tmp->key, len) == 0 && tmp->key[len] == '\0')
		{
			var_value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (var_value);
}

int	expand(t_env_expand *ex)
{
	int		k;
	char	*var_name;
	char	*var_value;

	k = 0;
	var_name = get_env_key(ex, &k);
	if (!var_name)
		return (-1);
	var_value = search_env_list(ex->env, var_name, k);
	free(var_name);
	if (!var_value)
		return (-1);
	k = 0;
	while (var_value[k])
	{
		(ex->res)[ex->j] = var_value[k];
		k++;
		(ex->j)++;
	}
	return (0);
}

char	*expand_variables(char *rl, t_env *env)
{
	int				single_quote;
	t_env_expand	exp;

	single_quote = 0;
	exp.i = 0;
	exp.j = 0;
	exp.rl = rl;
	exp.env = env;
	exp.res = ft_calloc(ft_strlen(rl) + 1000, sizeof(char));
	if (!exp.res)
		return (NULL);
	while (rl[exp.i])
	{
		if (rl[exp.i] == '$' && single_quote == 0)
		{
			if (expand(&exp) == -1)
				exp.res[(exp.j)++] = rl[(exp.i)++];
		}
		else
			assign_char(&exp, &single_quote);
	}
	return (exp.res);
}
