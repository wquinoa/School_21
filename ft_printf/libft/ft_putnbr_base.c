/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 10:44:09 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/19 15:51:46 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_base(uint64_t n, uint8_t base)
{
	const uint8_t	len = ft_nlen(n, base);
	uint64_t		div;

	if (base == 16)
		write(1, "0x", 2);
	div = ft_pow(base, len - 1);
	while (div != 0)
	{
		ft_putchar_fd("0123456789ABCDEF"[n / div], 1);
		n %= div;
		div /= base;
	}
}
