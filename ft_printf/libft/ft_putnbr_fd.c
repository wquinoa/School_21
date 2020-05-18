/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:24:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/04/30 17:23:57 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int d;

	d = 1000000000;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putstr_fd("2147483648", fd);
			return ;
		}
		n = -n;
	}
	while (d > n)
		d /= 10;
	while (d >= 10)
	{
		ft_putchar_fd((n / d) + '0', fd);
		n %= d;
		d /= 10;
	}
	ft_putchar_fd(n + '0', fd);
}
