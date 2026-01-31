/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:07:18 by pkosciel          #+#    #+#             */
/*   Updated: 2026/01/31 14:52:19 by jziola           ###   ########.fr       */
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
	int		end;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	start = 0;
	while (start < len && is_whitespace(input[start]))
		start++;
	end = len;
	while (end > start && is_whitespace(input[end - 1]))
		end--;
	return (ft_substr(input, start, end - start));
}
