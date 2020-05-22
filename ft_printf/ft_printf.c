/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/22 00:41:50 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "src/libftprintf.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

//static void	ft_padding(t_spec *specifier)

static void		ft_clear_struct(t_spec *specifier)
{
	specifier->base = 0;
	specifier->flags = 0;
	specifier->precision = 0;
	specifier->type = 0;
	specifier->width = 0;
}

//void			ft_addprefix()

void		ft_pad(char p_type, int len)//, t_uint8 base)
{
	static const char	*type = "        00000000";
	const t_uint8		i = 8;
	char				*padding;

	//ft_addprefix(base);
	//if (base & is_neg)
		//write(1, "-", 1);
	padding = (p_type == '0') ? (char *)&type[i] : (char *)type;
	while (len > i)
		len -= write(1, padding, i);
	if (len > 0)
		write(1, padding, len);
}

static void	ft_print_int(va_list arg, t_spec *s)
{
	const int		num = va_arg(arg, long);
	const char		type = s->type;
	const t_uint8	*base = &(s->base);
	const t_uint8	len = ft_nlen_sig(num, *base);

	s->width -= ft_max(s->precision, len);
	s->precision -= len;
	//if (!(s->flags & minus_f))
		ft_pad((s->flags & zero_f) ? '0' : ' ', s->width);// , *base + is_neg * (num < 0));
//	ft_pad('0', s->precision, *base + is_neg * (num < 0));
	if (type == 'd' || type == 'i')
		ft_putnbr_base(num, *base, s);
	else if (type == 'c' || type == '%')
		ft_putchar_fd((char)num, 1);
	if (s->flags & minus_f)
		ft_pad(' ', s->width);//, *base);
}

static void		ft_print_unsigned(va_list arg, t_spec *s)
{
	const t_uint64	number = va_arg(arg, unsigned long long);
	const t_uint8	*base = &(s->base);
	const t_uint8	len = ft_nlen(number, *base);
	const t_uint8	is_ptr = ((s->type == 'p'));

	s->width -= ft_max(s->precision, len) + (is_ptr * 2);
	s->precision -= len;
	if (!(s->flags & minus_f))
		ft_pad((s->flags & zero_f) ? '0' : ' ', s->width);//, *base);
	//ft_pad('0', s->precision);//, *base + (hex * is_ptr));
	if (s->type == 'X')
		ft_putull_base((t_uint16)number, (*base + upper), s);
	else if (s->type == 'x')
		ft_putull_base((t_uint16)number, *base, s);
	else if (s->type == 'p')
		ft_putull_base(number, *base + hex, s);
	else if (s->type == 'u')
		ft_putull_base((t_uint16)number, *base, s);
	if (s->flags & minus_f)
		ft_pad(' ', s->width);//, *base);
}


static int	ft_specs_padding(const char type, va_list arg, t_spec *specifier)
{
	const char	*is_numeric = ft_strchr(&SPECS[3], type);
	t_uint8		*base;
	//size_t		len;

	specifier->type = type;
	base = &(specifier->base);
	*base = (type == 'x' || type == 'X' || type == 'p') ? 16 : 10;
	if (is_numeric)
	{
		if (*base == 16 || type == 'u')
			ft_print_unsigned(arg , specifier);
		else if (*base == 10)
			ft_print_int(arg, specifier);
	}
	else if (type == 's')
		ft_putstr_fd(va_arg(arg, char *), 1);
	return (1);
}

static int	ft_flags(char *c, uint8_t *flags, int *width, int *precisn, \
					va_list arg)
{
	int	size;

	size = (ft_isdigit(*c)) ? ft_atoi(c) : 0;
	if (*c == '.')
		*flags += dot_f;
	if (*c == '-')
		*flags += minus_f;
	if (*c == '0')
		*flags += zero_f * ((*flags & minus_f) == 0);
	if (*c == '*' || size)
	{
		if (*c == '*')
			size = va_arg(arg, int);
		*flags += (*flags & dot_f) ? precision2_f : width1_f;
		(*flags & dot_f) ? (*precisn = size) : (*width = size);
		if (*c == '*')
		{
			va_end(arg);
			return (1);
		}
		return ((*flags & dot_f) ? ft_nlen(*precisn, 10) : ft_nlen(*width, 10));
	}
	return (1);
}

int			ft_printf(const char *str, ...)
{
	const char		*end = str;
	static t_spec	s;
	va_list			ap;

	va_start(ap, str);
	while (*str)
	{
		ft_clear_struct(&s);
		if ((end = ft_strchr(str, '%')))
		{
			str += write(1, str, end - str);
			end++;
			while (*end && (ft_strchr(FLAGS, *end) || ft_isdigit(*end)))
				end += ft_flags((char *)end, &(s.flags), \
								&(s.width), &(s.precision), ap);
			if (ft_strchr(SPECS, *end))
			{
				end += ft_specs_padding(*end, ap, &s);
				str = end;
			}
		}
		else
			str += write(1, str, ft_strlen(str));
	}
	va_end(ap);
	return (0);
}

int			main(void)
{
	//char const *test = "%23.15u, %d\n";
	char const *test = "%-0*p\n";
	//ft_printf(test, 23, 15, c);
	//printf(test, 23,15 ,c);
	//char *s = "hi";
	int c = -219837;//'B';
	ft_printf(test, 16, c);
	printf(test, 16 , c);
}
