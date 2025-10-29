/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:35:14 by jziola            #+#    #+#             */
/*   Updated: 2025/01/13 17:18:58 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*arr;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		size++;
	arr = malloc(sizeof(char) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (src[i])
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
