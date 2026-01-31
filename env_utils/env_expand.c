/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:52 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/31 15:03:05 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "env_utils.h"

int	expand_last_status(t_env_expand *ex)
{
	char	*st;
	int		k;

	if (ex->rl[ex->i + 1] != '?')
		return (-1);
	st = env_get(ex->env, "?");
	if (st)
	{
		k = 0;
		while (st[k])
			ex->res[ex->j++] = st[k++];
	}
	ex->i += 2;
	return (0);
}

int	expand(t_env_expand *ex)
{
	char	*var_name;
	char	*var_value;
	int		k;

	if (expand_last_status(ex) == 0)
		return (0);
	var_name = get_env_key(ex);
	if (!var_name)
		return (-1);
	var_value = search_env_list(ex->env, var_name, ft_strlen(var_name));
	free(var_name);
	if (!var_value)
		return (0);
	k = 0;
	while (var_value[k])
		ex->res[ex->j++] = var_value[k++];
	return (0);
}

static void	handle_dollar(t_env_expand *exp, int *single_quote)
{
	int	old_i;

	(void)single_quote;
	old_i = exp->i;
	if (expand(exp) == -1)
	{
		exp->i = old_i;
		exp->res[exp->j++] = exp->rl[exp->i++];
	}
}

static void	init_expand(t_env_expand *exp, char *rl, t_env *env)
{
	exp->i = 0;
	exp->j = 0;
	exp->rl = rl;
	exp->env = env;
	exp->res = ft_calloc(ft_strlen(rl) + 1000, sizeof(char));
}

char	*expand_variables(char *rl, t_env *env)
{
	t_env_expand	exp;
	int				single_quote;

	if (!rl)
		return (NULL);
	single_quote = 0;
	init_expand(&exp, rl, env);
	if (!exp.res)
		return (NULL);
	while (rl[exp.i])
	{
		if (rl[exp.i] == '$' && single_quote == 0)
			handle_dollar(&exp, &single_quote);
		else
			assign_char(&exp, &single_quote);
	}
	return (exp.res);
}
