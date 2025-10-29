/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:53:52 by jziola            #+#    #+#             */
/*   Updated: 2025/01/12 15:52:48 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			altc;

	altc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == altc)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == altc)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
