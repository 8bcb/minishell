/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:52 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/31 14:55:19 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "env_utils.h"

void	assign_char(t_env_expand *var, int *single_quote, int *double_quote)
{
	if (var->rl[var->i] == 34) 
	{
		if (!(*double_quote))
			*double_quote = 1;
		else
			*double_quote = 0;
	}
	if (var->rl[var->i] == 39 && !*double_quote)
	{
		if (*single_quote == 0)
			*single_quote = 1;
		else
			*single_quote = 0;
	}
	var->res[(var->j)++] = var->rl[(var->i)++];
}

static int is_var_start(int c)
{
    return (ft_isalpha(c) || c == '_');
}

static int is_var_char(int c)
{
    return (ft_isalnum(c) || c == '_');
}

char *get_env_key(t_env_expand *ex)
{
    int start;
    int k;

    k = ex->i + 1;
    if (!ex->rl[k] || !is_var_start((unsigned char)ex->rl[k]))
        return (NULL);

    start = k;
    while (ex->rl[k] && is_var_char((unsigned char)ex->rl[k]))
        k++;

    ex->i = k;
    return (ft_substr(ex->rl, start, k - start));
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

int expand_last_status(t_env_expand *ex)
{
	char *st;
	int k;
	
	if (ex->rl[ex->i + 1] == '?')
	{
		st = env_get(ex->env, "?");
		if (st)
		{
			k = 0;
			while (st[k])
				ex->res[ex->j++] = st[k++];
		}
		ex->i += 2; /* consume "$?" */
		return (0);
	}
	return -1;
}

int	expand(t_env_expand *ex)
{
	int		k;
	char	*var_name;
	char	*var_value;

	if (expand_last_status(ex) == 0)
		return (0);
	k = 0;
	var_name = get_env_key(ex);
	if (!var_name)
		return (-1);
	var_value = search_env_list(ex->env, var_name, ft_strlen(var_name));
	free(var_name);
	if (!var_value)
		return (0);
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
	int				double_quote;
	t_env_expand	exp;

	single_quote = 0;
	double_quote = 0;
	exp.i = 0;
	exp.j = 0;
	exp.rl = rl;
	exp.env = env;
	if (ft_strlen(rl) == 0)
		return (NULL);
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
			assign_char(&exp, &single_quote, &double_quote);
	}
	return (exp.res);
}
