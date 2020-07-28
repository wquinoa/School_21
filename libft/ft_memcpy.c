/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:18:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 17:47:01 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Reworked memcpy to copy in blocks of up to a long per cycle
**	The memory has to be aligned into a suitable block
**	byte by byte first.
*/

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	const unsigned char	size = sizeof(unsigned long);
	const unsigned char	*c2 = (unsigned char *)(src);
	unsigned char		*c1;
	unsigned long		*a1;
	unsigned long		*a2;

	c1 = (unsigned char *)dst;
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
