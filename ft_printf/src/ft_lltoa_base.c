/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 10:44:09 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/17 02:53:34 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static long long		ft_numlen(long long n, unsigned char base)
{
	int				i;

	i = 0;
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}

static long long		ft_pw(long long n, int pow)
{
	long long			res;

	if (pow == 0 || n == 1)
		return (1);
	if (pow < 0)
		return (-1);
	res = 1;
	while (pow--)
		res *= n;
	return (res);
}


void			ft_lltoa_base(size_t n, uchar_t base)
{
	const uchar_t		len;
	uchar_t		i = 0;
	size_t		div;

	len = ft_numlen(n, base);
	div = ft_pow(base, len - 1);
	while (div != 0)
	{
		ft_putchar_fd("0123456789ABCDEF"[n / div], 1);
		n %= div;
		div /= base;
	}
}
int		main(void)
{
	ft_lltoa_base(1600000, 16);
}
