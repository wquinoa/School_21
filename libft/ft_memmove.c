/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:34:42 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 17:32:06 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	uint8_t	*a;
	uint8_t	*b;
	size_t	i;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	i = 0;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
		while (++i <= len)
			a[len - i] = b[len - i];
	return (dst);
}
