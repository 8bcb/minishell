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

#include "minishell.h"

int isWhiteSpace(char c) {
	if ((c >= 9 && c <= 13) || c == 32)
		return 1;
	return 0;
}

int countWords(char *str) {
	int counter = 0;
	int i = 0;
	int isQuoted = -1;
	while (str[i] && str[i] <= 32)
		i++;
	while (str[i + 1]) {
		if (str[i] ==  34 || str[i] == 39)
			isQuoted = (isQuoted == -1) ? 1 : -1;
		else if (isWhiteSpace(str[i]) == 1 && isWhiteSpace(str[i + 1]) == 0 && isQuoted == -1)
			counter++;
		i++;
	}
	return counter + 1;
}

void omitWhiteSpaces(char *str, int *i) {
	while (isWhiteSpace(str[*i]) == 1)
		(*i)++;
}

void add_node(s_node* list, Token *newToken) {
	s_node *newNode;
	s_node *tail;

	tail = list;
	while (tail->next != NULL)
		tail = tail->next;
	if (list->val.value == NULL) {
		list->val = *newToken;
	}
	else {
		newNode = (s_node *)malloc(sizeof(s_node));
		if (!newNode)
			return;
		newNode->val = *newToken;
		newNode->next = NULL;
		tail->next = newNode;
	}
}

int command_or_assignment(char* input, s_node *list, int start)
{
	int i = start;
	Token newToken;
	newToken.type = COMMAND;
	while (input[i] && isWhiteSpace(input[i]) != 1) {
		if (input[i] == '=')
			newToken.type = ASSIGNMENT;
		i++;
	}
	newToken.value = ft_substr(input, start - 1, i - start + 2);
	add_node(list, &newToken);
	return i - start;
}

int option(char* input, s_node *list, int start) {
	int i = start;
	Token newToken;
	while(input[i] && isWhiteSpace(input[i]) != 1)
		i++;
	newToken.type = OPTION;
	newToken.value = ft_substr(input, start - 1, i - start + 2);
	add_node(list, &newToken);
	return i - start;
}

int argument(char* input, s_node* list, int start) {
	int i = start;
	Token newToken;
	if (start == 34) {

	}
	else if (start == 39) {

	}
	else {
		while (input[i] && isWhiteSpace(input[i]) != 1)
			i++;
	}
	newToken.value = ft_substr(input, start - 1, i - start + 2);
	newToken.type = ARGUMENT;
	add_node(list, &newToken);
	return i - start;
}

void scanInput(char* input, s_node *head)
{
	//const char *operators[] = {">>", "<<", "> ", "< ", "| "};
	int i = 0;
	int isQuoted = 0;
	int commandExist = 0;
	while (input[i]) { 
		if (!isQuoted && isWhiteSpace(input[i]))
			omitWhiteSpaces(input, &i);
		if (((input[i] >= 65 && input[i] <= 90) || 
		(input[i] >= 97 && input[i] <= 122))) {
			if (!commandExist) {
				i += command_or_assignment(input, head, i);
				commandExist = 1;
			}
			else
			 	i += argument(input, head, i);
		}
		if (!isQuoted && input[i] == 45)
		 	i += option(input, head, i);
		if (input[i] == 60 || input[i] == 62 || input[i] == 124) {
			commandExist = 0;
		}
		// else if (input[i] == 34)
		// 	isQuoted = (isQuoted == -1) ? 1 : -1;
		// else if (input[i] == 39)
		// 	isQuoted = (isQuoted == -1) ? 2 : -1;
		i++;
	}
	while(head != NULL)
	{
		printf("Token %d: %s\n",(int)head->val.type, head->val.value);
		head = head->next;
	}
	printf("%s\n", input);
}

