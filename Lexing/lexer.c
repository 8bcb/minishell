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

s_node* tokenizing(char* input, int* isAssignment)
{
	s_node *head;
	int i = 0;
	char* trimmed;
	int increment;

	head = NULL;
	trimmed = trim(input);
	*isAssignment = isValidAssignment(trimmed);
	increment = 0;
	if (*isAssignment == 1 || *isAssignment == -1)
		return NULL;
	while (trimmed[i])
	{
		if (trimmed[i] == '<' || trimmed[i] == '>')
			increment = t_redirection(trimmed, &head, i);
		else if (trimmed[i] == '|')
			increment = t_pipe(&head);
		else if (isWhiteSpace(trimmed[i]) == 0 || trimmed[i] == 34 || trimmed[i] == 39)
			increment = t_argument(trimmed, &head, i);
		else if (isWhiteSpace(trimmed[i]) == 1)
			increment = 1;
		if (increment == -1)
		{
			free_list(&head);
			free(trimmed);
			return NULL;
		}
		i += increment;
	}
	free(trimmed);
	return head;
}