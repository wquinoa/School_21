/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:24:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 00:12:55 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int d;
	int i;

	d = 1000000000;
	i = (n < 0);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
			return (ft_putstr_fd("2147483648", fd) + 1);
		n = -n;
	}
	while (d > n)
		d /= 10;
	while (d >= 10)
	{
		i += ft_putchar_fd((n / d) + '0', fd);
		n %= d;
		d /= 10;
	}
	return (i + ft_putchar_fd(n + '0', fd));
}
