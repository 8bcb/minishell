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
	int i;
	int hasEqualsSign;
	int openQuote;

	i = 0;
	hasEqualsSign = 0;
	openQuote = 0;
	if (isAlphanumeric(str[i]) == 1 && (str[i] >= 48 && str[i] <= 57))
		return 0;
	while (str[i]) 
	{
		if (openQuote == 0 && str[i] == '=')
			hasEqualsSign++;
		else if (str[i] == 34 || str[i] == 39)
			openQuote = (openQuote == 0 ? str[i] : 0);
		else if (openQuote == 0 && (isWhiteSpace(str[i]) == 1
			|| isAlphanumeric(str[i]) == 0))
			return 0;
		i++;
	}
	return (hasEqualsSign == 1 && openQuote == 0) ? 1 : 0;
}

void t_assignment(char* str, s_node* head)
{
	Token newToken;

	newToken.type = ASSIGNMENT;
	newToken.value = str;
	add_node(head, &newToken);
}

void scanInput(char* input, s_node *head)
{
	int i = 0;
	int commandExist = 0;
	char* trimmed;

	trimmed = trim(input);
	if (isValidAssignment(trimmed) == 1)
	{
		t_assignment(trimmed, head);
		return;
	}
	while (trimmed[i]) { 
		if (trimmed[i] == 34 || trimmed[i] == 39)
			i += t_argument(trimmed, head, i);
		else if (trimmed[i] == '<' || trimmed[i] == '>')
			i += t_redirection(trimmed, head, i);
		else if (trimmed[i] == '|')
			i += t_pipe(head, &commandExist);
		else if (isWhiteSpace(trimmed[i]) == 0) {
			if (commandExist == 1)
				i += t_argument(trimmed, head, i);
			else
				i += t_command(trimmed, head, i, &commandExist);
		}
		i++;
	}
	while(head != NULL)
	{
		printf("Token %d: %s\n",(int)head->val.type, head->val.value);
		head = head->next;
	}
}

