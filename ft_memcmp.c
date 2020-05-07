/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:24:47 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/01 10:07:06 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if ((!*a && !*b) || n == 0)
		return (0);
	while (*a == *b && ++i < n)
	{
		a++;
		b++;
	}
	return (*a - *b);
}
