#include "../minishell.h"

void add_node(s_node* list, Token *newToken) 
{
	s_node *newNode;
	s_node *tail;

	tail = list;
	if (list->val.value == NULL) 
	{
		list->val = *newToken;
		list->next = NULL;
	}
	else 
	{
		while (tail->next != NULL)
			tail = tail->next;
		newNode = (s_node *)malloc(sizeof(s_node));
		if (!newNode)
			return;
		newNode->val = *newToken;
		newNode->next = NULL;
		tail->next = newNode;
	}
}

void printList(s_node *head) {
	while(head != NULL)
	{
		printf("Token %d: %s\n",(int)head->val.type, head->val.value);
		head = head->next;
	}
}