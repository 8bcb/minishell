/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:30:22 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/24 11:13:59 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equals_count(int *equals_count)
{
	if (*equals_count == 0)
		return (0);
	else
		return (_invalid_assignment_error());
}

int	scan_for_assignment(char *str, int *equals_count, int *open_quote)
{
	while (*str)
	{
		if (*open_quote == 0 && *str == '=')
		{
			(*equals_count)++;
			if (*equals_count > 1)
				return (_invalid_assignment_error());
		}
		else if (((*str == 34 || *str == 39) && *open_quote == 0)
			|| (*str == *open_quote && *open_quote != 0))
		{
			if ((*open_quote) == 0)
				*open_quote = *str;
			else
				*open_quote = 0;
		}
		else if (*open_quote == 0 && is_whitespace(*str) == 1)
			return (check_equals_count(equals_count));
		str++;
	}
	return (1);
}

int	is_valid_assignment(char *str)
{
	int	equals_count;
	int	open_quote;
	int	scan_result;

	equals_count = 0;
	open_quote = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	scan_result = scan_for_assignment(str, &equals_count, &open_quote);
	if (scan_result != 1)
		return (scan_result);
	if (open_quote != 0)
		return (_unclosed_quotes_error());
	if (equals_count == 1)
		return (1);
	return (0);
}

int	tokenize_input(char *input, t_node **list)
{
	int	i;
	int	increment;

	i = 0;
	increment = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			increment = t_redirection(input, list, i);
		else if (input[i] == '|')
			increment = t_pipe(list);
		else if (is_whitespace(input[i]) == 0 || input[i] == 34
			|| input[i] == 39)
			increment = t_word(input, list, i);
		else if (is_whitespace(input[i]) == 1)
			increment = 1;
		if (increment == -1)
			return (-1);
		i += increment;
	}
	return (1);
}

t_node	*lexing(char *input, int *isAssignment)
{
	t_node	*head;
	char	*trimmed;
	int		success;

	head = NULL;
	trimmed = trim(input);
	if (!trimmed)
		return (NULL);
	*isAssignment = is_valid_assignment(trimmed);
	if (*isAssignment == 1 || *isAssignment == -1
		|| !valid_first_sign(trimmed[0]))
	{
		if (!valid_first_sign(trimmed[0]))
			_invalid_input();
		free(trimmed);
		return (NULL);
	}
	success = tokenize_input(trimmed, &head);
	free(trimmed);
	if (success == -1)
	{
		free(head);
		return (NULL);
	}
	return (head);
}
