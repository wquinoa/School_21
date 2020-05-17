/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:12:06 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/12 15:42:35 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *src = (unsigned char *)s;
	const unsigned char a = (unsigned char)c;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (src[i] == a)
			return ((void *)&src[i]);
		i++;
	}
	return (NULL);
}
