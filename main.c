/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkosciel <pkosciel@student.42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:40:14 by pkosciel          #+#    #+#             */
/*   Updated: 2025/10/11 11:20:12 by pkosciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void) 
{
	char *rl;
	s_node *head;
	head = (s_node *)malloc(sizeof(s_node));
	if (!head)
		return 1;
	printf("Head: %s\n", head->val.value);
	while (1) {
		rl = readline("Prompt > ");
		scanInput(rl, head);
		//parseInput
		//execute
	}
	return 0;
}