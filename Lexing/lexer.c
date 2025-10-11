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
	while (str[i] && str[i] <= 32)
		i++;
	while (str[i + 1]) {
		if (isWhiteSpace(str[i]) == 1 && isWhiteSpace(str[i + 1]) == 0)
			counter++;
		i++;
	}
	return counter + 1;
}

void scanInput(char* input)
{
	printf("Words: %d\n",countWords(input));
	printf("%s\n", input);
}

