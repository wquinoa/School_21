/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 10:44:09 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 18:14:42 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**	Since base had some free bits, I've put some info in them
*/

static t_uint8	ft_decypher(uint8_t *base)
{
	int	code;

	code = *base & upper;
//	code += (*base & hash_f);
	*base &= ~(upper);// | hash_f);
	return (code);
}

void			ft_putnbr_base(uint64_t n, uint8_t base)//, int padding)
{
	const t_uint8	code = ft_decypher(&base);
	const t_uint8	len = ft_nlen(n, base);
	t_uint64		div;

	div = ft_pow(base, len - 1);
	while (div != 0)
	{
		if (code & upper)
			ft_putchar_fd(ft_toupper(BASE[n / div]), 1);
		else
			ft_putchar_fd(BASE[n / div], 1);
		n %= div;
		div /= base;
	}
}

//void			ft_padding(t_uint64 n, t_uint8 base, char *str, t_spec *specifier)
//{
	//const int	padding = specifier->width;

	//number *= (number < 0) ? -1 : 1;
	//if (padding > 0 && (specifier->flags & minus_f))

//}
