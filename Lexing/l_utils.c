/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:07:18 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/24 15:53:53 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*trim(char *input)
{
	int		len;
	int		start;
	int		j;
	int		iter;
	char	*res;

	start = 0;
	len = ft_strlen(input);
	while (input[start] && is_whitespace(input[start]) == 1)
		start++;
	j = 0;
	iter = len - 1;
	while (input[iter] && is_whitespace(input[iter]) == 1)
	{
		j++;
		iter--;
	}
	res = ft_substr(input, start, len - start - j);
	if (!res)
		return (NULL);
	return (res);
}
