/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:49:19 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/31 15:00:58 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_argv(char *str, t_ast **node)
{
	int		i;
	char	*new_arg;

	i = 0;
	while ((*node)->argv[i])
		i++;
	if (i > 8)
		return (_too_many_args_error());
	new_arg = ft_strdup(str);
	if (!new_arg)
		return (-1);
	(*node)->argv[i] = new_arg;
	return (1);
}

int	update_redir_list(char ***list, char **str)
{
	int	i;

	i = 0;
	if (*list == NULL)
		*list = calloc(10, sizeof(char *));
	if (!*list)
		return (-1);
	while ((*list)[i])
		i++;
	if (i > 8)
		return (_too_many_args_error());
	(*list)[i] = *str;
	return (1);
}

int	assign_redir_values(t_ast **node, char	**file, t_token_type type)
{
	int	rez;

	rez = 0;
	if (type == REDIR_IN)
		rez = update_redir_list(&((*node)->infile), file);
	else if (type == HEREDOC)
	{
		(*node)->heredoc = 1;
		(*node)->heredoc_tmp = *file;
	}
	else
	{
		rez = update_redir_list(&((*node)->outfile), file);
		if (type == REDIR_APPEND)
			(*node)->append = 1;
	}
	return (rez);
}
