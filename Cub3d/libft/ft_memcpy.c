/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:18:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/31 21:07:34 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Reworked memcpy to copy in blocks of up to 8 bytes per cycle
**	The memory has to be aligned into a suitable block
**	byte by byte first. uint_8t is unsigned char.
*/

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	const uint8_t	size = sizeof(unsigned long);
	const uint8_t	*c2 = (uint8_t *)(src);
	uint8_t			*c1;
	unsigned long	*a1;
	unsigned long	*a2;

	c1 = (uint8_t *)dst;
	while (n % size)
	{
		*(c1++) = *(c2++);
		n--;
	}
	a1 = (unsigned long *)(c1);
	a2 = (unsigned long *)(c2);
	while (n >= size)
	{
		*(a1++) = *(a2++);
		n -= size;
	}
	return (dst);
}
