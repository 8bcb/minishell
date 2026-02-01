/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asia <asia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:49:19 by pkosciel          #+#    #+#             */
/*   Updated: 2026/02/01 13:41:59 by asia             ###   ########.fr       */
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

static int	init_redir_arrays(char ***files, int **modes)
{
	if (*files == NULL)
		*files = calloc(10, sizeof(char *));
	if (*modes == NULL)
		*modes = calloc(10, sizeof(int));
	if (!*files || !*modes)
		return (-1);
	return (0);
}

int	update_redir_list_with_mode(char ***files, int **modes,
		char **file, int append)
{
	int	i;

	if (init_redir_arrays(files, modes) != 0)
		return (-1);
	i = 0;
	while ((*files)[i])
		i++;
	if (i > 8)
		return (_too_many_args_error());
	(*files)[i] = *file;
	(*modes)[i] = append;
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

int	assign_redir_values(t_ast **node, char **file, t_token_type type)
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
		rez = update_redir_list_with_mode(&((*node)->outfile),
				&((*node)->out_append), file,
				(type == REDIR_APPEND));
	}
	return (rez);
}
