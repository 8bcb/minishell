/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:16:57 by jziola            #+#    #+#             */
/*   Updated: 2025/01/12 20:53:18 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	character_to_find;

	str = (unsigned char *)s;
	character_to_find = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == character_to_find)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
