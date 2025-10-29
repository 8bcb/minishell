/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:34 by jziola            #+#    #+#             */
/*   Updated: 2025/01/12 21:46:48 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dest, const char *src, int *index)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[*index] = src[i];
		i++;
		(*index)++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		index;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	index = 0;
	ft_strcpy(str, s1, &index);
	ft_strcpy(str, s2, &index);
	str[index] = '\0';
	return (str);
}
