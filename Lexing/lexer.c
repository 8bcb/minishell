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
	int hasEqualsSign;
	int openQuote;
	int hasInvalidCharacters;
	int isValid;

	hasEqualsSign = 0;
	openQuote = 0;
	hasInvalidCharacters = 0;
	if (ft_isalpha(*str) == 0 && *str != '_')
		return 0;
	while (*str) 
	{
		if (openQuote == 0 && *str == '=')
			hasEqualsSign++;
		else if (((*str == 34 || *str == 39) && openQuote == 0 ) || (*str == openQuote && openQuote != 0))
			openQuote = (openQuote == 0 ? *str : 0);
		else if (openQuote == 0 && isWhiteSpace(*str) == 1)
			hasInvalidCharacters = 1;
		str++;
	}
	isValid = ((hasEqualsSign == 1 && openQuote != 0) || (hasEqualsSign == 1 && hasInvalidCharacters == 1)) ? -1 : 1;
	if (hasEqualsSign == 1 && openQuote != 0)
		_unclosed_quotes_error();
	if (hasEqualsSign == 1 && hasInvalidCharacters == 1)
		_invalid_assignment_error();
	return hasEqualsSign == 0 ? 0 : isValid;
}

void t_assignment(char* str, s_node **head)
{
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return ;
	newToken->type = ASSIGNMENT;
	newToken->value = str;
	add_node(head, &newToken);
}

s_node* scanInput(char* input, int* isAssignment)
{
	s_node *head;
	int i = 0;
	int commandExist = 0;
	char* trimmed;
	int increment;

	head = NULL;
	trimmed = trim(input);
	*isAssignment = isValidAssignment(trimmed);
	increment = 0;
	if (*isAssignment == 1 || *isAssignment == -1)
	{
		if (*isAssignment == 1)
			t_assignment(trimmed, &head);
		return NULL;
	}
	while (trimmed[i]) { 
		if (trimmed[i] == 34 || trimmed[i] == 39) {
			increment = t_argument(trimmed, &head, i);
			if (increment == -1)
				return NULL;
			i += increment;
		}
		else if (trimmed[i] == '<' || trimmed[i] == '>')
			i += t_redirection(trimmed, &head, i);
		else if (trimmed[i] == '|')
			i += t_pipe(&head, &commandExist);
		else if (isWhiteSpace(trimmed[i]) == 0) {
			if (commandExist == 1)
				i += t_argument(trimmed, &head, i);
			else
				i += t_command(trimmed, &head, i, &commandExist);
		}
		i++;
	}
	return head;
}

