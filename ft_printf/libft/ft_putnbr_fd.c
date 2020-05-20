/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:24:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 12:35:53 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static void	ft_putnbr_base_fd(size_t n, t_uint8 base, int fd)
{
	const t_uint8	len = ft_nlen(n, base);
	t_uint64		div;

	div = ft_pow(base, len - 1);
	while (div != 0)
	{
		ft_putchar_fd(BASE[n / div], fd);
		n %= div;
		div /= base;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n == INT32_MIN)
	{
		write(fd, "2147483648", 10);
		return ;
	}
	ft_putnbr_base_fd((n > 0) ? n : (size_t)(-n), 10, fd);
}
