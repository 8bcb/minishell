#include "../minishell.h"

void add_node(s_node** list, Token **newToken) 
{
	s_node *newNode;
	s_node *tail;

	tail = *list;
	newNode = malloc(sizeof(s_node));
	if (!newNode)
		return;
	newNode->val = *newToken;
	newNode->next = NULL;
	if (*list == NULL)
		*list = newNode;
	else 
	{
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = newNode;
	}
}

void free_list(s_node **list) {
	s_node* tmp;

	tmp = NULL;
	while (*list != NULL) {
		tmp = *list;
		*list = (*list)->next;
		//if (tmp->val.value != NULL)
			//free(tmp->val.value);
		free(tmp);
	}
}

void print_list(s_node *head) {
	s_node *curr = head;
	while(curr != NULL)
	{
		printf("Token %d: %s\n",curr->val->type, curr->val->value);
		curr = curr->next;
	}
}