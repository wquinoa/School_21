/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 12:35:38 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/22 15:35:07 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

void		ft_pad(char p_type, int len)
{
	static const char	*type = "        00000000";
	const t_uint8		i = 8;
	char				*padding;

	padding = (p_type == '0') ? (char *)&type[i] : (char *)type;
	while (len > i)
		len -= write(1, padding, i);
	if (len > 0)
		write(1, padding, len);
}

static void	ft_print_signed(va_list arg, t_spec *s)
{
	const int		num = va_arg(arg, long);
	const t_uint8	*base = &(s->base);
	const t_uint8	len = ft_nlen(num, *base);

	s->width -= (ft_max(s->precision, len) + (num < 0));
	s->precision -= len;
	if (!(s->flags & z_and_m))
		ft_pad(' ', s->width);
	if (s->type == 'd' || s->type == 'i')
		ft_putnbr_base(num, *base, s);
	if (s->flags & minus_f)
		ft_pad(' ', s->width);
}

static void	ft_print_unsigned(va_list arg, t_spec *s)
{
	const t_uint64	number = va_arg(arg, unsigned long long);
	const t_uint8	*base = &(s->base);
	const t_uint8	len = ft_nlen(number, *base);
	const t_uint8	is_ptr = ((s->type == 'p'));

	s->width -= (ft_max(s->precision, len) + (is_ptr * 2));
	s->precision -= len;
	if (!(s->flags & z_and_m))
		ft_pad(' ', s->width);
	if (s->type == 'X')
		ft_putull_base((t_uint16)number, (*base + upper), s);
	else if (s->type == 'x')
		ft_putull_base((t_uint16)number, *base, s);
	else if (s->type == 'p')
		ft_putull_base(number, *base + hex, s);
	else if (s->type == 'u')
		ft_putull_base((t_uint16)number, *base, s);
	if (s->flags & minus_f)
		ft_pad(' ', s->width);
}

static void	ft_print_str(va_list arg, t_spec *s)
{
	const char		*str = va_arg(arg, char *);
	const char		c = (const char)str;
	const t_uint16	len = (str && s->type == 's') ? ft_strlen(str) : 0;

	if (s->type != 's')
		s->precision = 0;
	s->width -= (ft_min(s->precision, len) + (s->type != 's'));
	if ((s->flags & minus_f) == 0)
		ft_pad(' ', s->width);
	if (s->type == 's')
	{
		if (!str)
			write(1, "(null)", 6);
		write(1, str, s->precision);
	}
	else if (s->type == 'c' || s->type == '%')
		write(1, (s->type == 'c') ? &c : "%", 1);
	if (s->flags & minus_f)
		ft_pad(' ', s->width);
}

int			ft_define_type(const char type, va_list arg, t_spec *specifier)
{
	const char	*is_numeric = ft_strchr(&SPECS[3], type);
	t_uint8		*base;

	specifier->type = type;
	base = &(specifier->base);
	*base = (type == 'x' || type == 'X' || type == 'p') ? 16 : 10;
	if (is_numeric)
	{
		if (*base == 16 || type == 'u')
			ft_print_unsigned(arg, specifier);
		else if (*base == 10)
			ft_print_signed(arg, specifier);
	}
	else
		ft_print_str(arg, specifier);
	return (1);
}
