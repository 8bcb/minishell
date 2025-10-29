/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:24:18 by jziola            #+#    #+#             */
/*   Updated: 2025/01/13 17:11:29 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memmove_forward(unsigned char *d, const unsigned char *s,
		size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	ft_memmove_backward(unsigned char *d, const unsigned char *s,
		size_t n)
{
	while (n > 0)
	{
		d[n - 1] = s[n - 1];
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	if (d < s)
		ft_memmove_forward(d, s, n);
	else
		ft_memmove_backward(d, s, n);
	return (dest);
}
