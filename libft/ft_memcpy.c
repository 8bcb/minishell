/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:32:52 by jziola            #+#    #+#             */
/*   Updated: 2025/01/12 13:13:42 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*altdest;
	const unsigned char	*altsrc;

	altdest = (unsigned char *)dest;
	altsrc = (const unsigned char *)src;
	while (n > 0)
	{
		*altdest = *altsrc;
		altdest++;
		altsrc++;
		n--;
	}
	return (dest);
}
