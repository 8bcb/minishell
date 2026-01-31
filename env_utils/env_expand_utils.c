/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 00:00:00 by jziola            #+#    #+#             */
/*   Updated: 2026/01/31 15:33:39 by pkosciel         ###   ########.fr       */
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
	var->res[var->j++] = var->rl[var->i++];
}

static int	is_var_start(int c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_key(t_env_expand *ex)
{
	int	start;
	int	k;

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
