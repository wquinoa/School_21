/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 23:09:49 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/07 20:57:00 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t l;

	l = ft_strlen(src);
	if (!dstsize)
		return (l);
	i = -1;
	while (++i < (dstsize - 1) && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (l);
}
