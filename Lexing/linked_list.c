/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:42:53 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/18 16:51:26 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_node **list, t_token **newToken)
{
	t_node	*new_node;
	t_node	*tail;

	tail = *list;
	new_node = malloc(sizeof(t_node));
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

void	free_list(t_node **list)
{
	t_node	*tmp;

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

void	print_list(t_node *head)
{
	t_node	*curr;

	curr = head;
	while (curr != NULL)
	{
		printf("Token %d: %s\n", curr->val->type, curr->val->value);
		curr = curr->next;
	}
}
