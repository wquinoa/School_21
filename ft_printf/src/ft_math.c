/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:57:33 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/22 15:25:31 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

t_uint8			ft_nlen(t_uint64 n, t_uint8 base)
{
	t_uint8		i;

	i = (n == 0);
	while (n != 0 && ++i)
		n /= base;
	return (i);
}

t_uint64		ft_pow(size_t n, size_t pow)
{
	size_t		res;

	res = 1;
	while (pow--)
		res *= n;
	return (res);
}

int				ft_max(int a, int b)
{
	return ((a * (a >= b)) + (b * (b > a)));
}

int				ft_min(int a, int b)
{
	return ((a * (a <= b)) + (b * (b < a)));
}

size_t			ft_abs(int n)
{
	if (n == -2147483648)
		return (2147483647);
	return ((n < 0) ? -n : n);
}
