/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 09:30:22 by pkosciel          #+#    #+#             */
/*   Updated: 2025/10/11 12:07:15 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int isValidAssignment(char *str) 
{
	int equalsCount;
	int openQuote;

	equalsCount = 0;
	openQuote = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return 0;
	while (*str) 
	{
		if (openQuote == 0 && *str == '=')
		{
			equalsCount++;
			if (equalsCount > 1)
				return -1;
		}
		else if (((*str == 34 || *str == 39) && openQuote == 0 ) || (*str == openQuote && openQuote != 0))
			openQuote = (openQuote == 0 ? *str : 0);
		else if (openQuote == 0 && isWhiteSpace(*str) == 1)
		{
			if (equalsCount == 0)
				return 0;
			else
				return _invalid_assignment_error();
		}
		str++;
	}
	if (openQuote != 0)
		return _unclosed_quotes_error();
	if (equalsCount == 1)
		return 1;
	return 0;
}

int tokenize_input(char* input, s_node** list)
{
	int i;
	int increment;

	i = 0;
	increment = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			increment = t_redirection(input, list, i);
		else if (input[i] == '|')
			increment = t_pipe(list);
		else if (isWhiteSpace(input[i]) == 0 || input[i] == 34 || input[i] == 39)
			increment = t_argument(input, list, i);
		else if (isWhiteSpace(input[i]) == 1)
			increment = 1;
		if (increment == -1)
			return -1;
		i += increment;
	}
	return 1;
}

s_node* lexing(char* input, int* isAssignment)
{
	s_node *head;
	char* trimmed;
	int success;

	head = NULL;
	trimmed = trim(input);
	*isAssignment = isValidAssignment(trimmed);
	if (*isAssignment == 1 || *isAssignment == -1 || !valid_first_sign(trimmed[0]))
	{
		if (!valid_first_sign(trimmed[0]))
			_invalid_input();
		free(trimmed);
		return NULL;
	}
	success = tokenize_input(trimmed, &head);
	free(trimmed);
	if (success == -1)
	{
		free(head);
		return NULL;
	}
	return head;
}