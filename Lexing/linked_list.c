/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:42:53 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 12:45:03 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(s_node **list, Token **newToken)
{
	s_node	*new_node;
	s_node	*tail;

	tail = *list;
	new_node = malloc(sizeof(s_node));
	if (!new_node)
		return ;
	new_node->val = *newToken;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = new_node;
	}
}

void	free_list(s_node **list)
{
	s_node	*tmp;

	tmp = NULL;
	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->val->value);
		free(tmp->val);
		free(tmp);
	}
}

void	print_list(s_node *head)
{
	s_node	*curr;

	curr = head;
	while (curr != NULL)
	{
		printf("Token %d: %s\n", curr->val->type, curr->val->value);
		curr = curr->next;
	}
}
