/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:47:30 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/07 00:43:13 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		l;
	size_t	ans;

	l = dstsize - ft_strlen(dst);
	ans = ft_strlen(src) + ft_strlen(dst);
	if (l > 0)
	{
		while (*dst)
			dst++;
		while (*src && --l)
			*(dst++) = *(src++);
		*dst = '\0';
	}
	return (ans + l * (l <= 0));
}
/*
**	l is the number of symbols to append. Cant append less than 1.
**	pseudocode (src + dst) + (dstisize - dst) only if dstsize is < dst
**	returns len(src + dst) and adds			l if l > 0.
**	returns len(src + dst) and subtracts	l if l < 0.
*/
