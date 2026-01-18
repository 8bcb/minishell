/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:49:33 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 16:51:45 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	t_word(char *input, t_node **list, int start)
{
	int		i;
	int		success;
	t_token	*new_token;
	char	*buffer;

	new_token = malloc(sizeof(t_token));
	buffer = calloc(ft_strlen(&(input[start])) + 1, sizeof(char));
	if (!new_token || !buffer)
		return (-1);
	i = start;
	success = add_to_buffer(input, &buffer, &i);
	if (!success)
	{
		free(buffer);
		free(new_token);
		return (_unclosed_quotes_error());
	}
	new_token->value = buffer;
	new_token->type = WORD;
	add_node(list, &new_token);
	return (i - start);
}

int	t_pipe(t_node **list)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (-1);
	new_token->type = PIPE;
	new_token->value = ft_strdup("|");
	add_node(list, &new_token);
	return (1);
}

int	t_redirection(char *input, t_node **list, int start)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (-1);
	set_redir_token_values(input, &new_token, start);
	if (!new_token->value)
	{
		free(new_token);
		return (_invalid_redirection_error());
	}
	add_node(list, &new_token);
	return (ft_strlen(new_token->value));
}
