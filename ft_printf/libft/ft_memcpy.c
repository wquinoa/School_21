/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:18:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/13 11:45:36 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	unsigned char		*a;
	unsigned char const	*b;

	if ((!dst && !src) || !n)
		return (dst);
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	while (n-- > 0)
		*(a++) = *(b++);
	return (dst);
}
