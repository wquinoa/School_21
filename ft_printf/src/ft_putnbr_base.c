/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 10:44:09 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/26 11:16:44 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

/*
**	Since 'base' had some free bits, I've put some info in them.
**	'base_bits' turns on bits up to 31, everything else is used for
**	flags. The two functions use a static buffer to print
**	the number it as a whole.
*/

static void		ft_alt(t_uint8 base, t_spec *s)
{
	if (base & hex)
		s->length += write(1, "0x", 2);
	else if (base & is_neg)
		s->length += write(1, "-", 1);
	if (s->flags & zero_f)
		s->precision = s->width;
}

void			ft_putull_base(uint64_t n, t_uint8 base, t_spec *s)
{
	const t_uint8	len = ft_nlen(n, (base & base_bits));
	static char		buf[21];
	t_uint64		div;
	t_uint8			i;

	ft_alt(base, s);
	if ((n == 0) && (s->precision <= 0) && (s->flags & precision2_f))
		return ;
	ft_pad('0', s->precision, s);
	i = 0;
	div = ft_pow((base & base_bits), len - 1);
	while (i < len)
	{
		if (base & upper)
			buf[i++] = ft_toupper(BASE[n / div]);
		else
			buf[i++] = BASE[n / div];
		n %= div;
		div /= (base & base_bits);
	}
	s->length += write(1, buf, len);
}

void			ft_putnbr_base(t_int64 n, t_uint8 base, t_spec *s)
{
	ft_putull_base((n < 0) ? -n : n, (base + (is_neg * (n < 0))), s);
}
