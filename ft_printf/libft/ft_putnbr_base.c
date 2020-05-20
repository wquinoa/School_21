/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 10:44:09 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 05:23:45 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../src/libftprintf.h"

/*
**	Since base had some free bits, I've put an uppercase flag there.
*/

void			ft_putnbr_base(uint64_t n, uint8_t base)
{
	const char		upcase = (base & upper) ? 'Y' : 'N';
	uint8_t			len = ft_nlen(n, (base &= ~upper));
	uint64_t		div;

	div = ft_pow(base, len - 1);
	while (div != 0)
	{
		if (upcase == 'Y')
			ft_putchar_fd(BASE[n / div], 1);
		else
			ft_putchar_fd(ft_tolower(BASE[n / div]), 1);
		n %= div;
		div /= base;
	}
}
