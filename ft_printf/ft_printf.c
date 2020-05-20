/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 18:22:49 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "src/libftprintf.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/*
** • The prototype of ft_printf should be int ft_printf(const char *, ...);
** • You have to recode the libc’s printf function
** • It must not do the buffer management like the real printf
** • It will manage the following conversions: cspdiuxX%
** • It will manage any combination of the following
**	flags: ’-0.*’ and minimum field
**   width with all conversions
** • It will be compared with the real printf
**
**
** • If the Mandatory part is not perfect don’t even think about bonuses
** • You don’t need to do all the bonuses
** • Manage one or more of the following conversions: nfge
** • Manage one or more of the following flags: l ll h hh
** • Manage all the following flags: ’# +’ (yes, one of them is a space)
*/

//printf("\nminus: %d\n", specifier.flags & minus_f);
//printf("zero : %d\n", specifier.flags & zero_f);
//printf("align: %d\n", specifier.flags & align1_f);
//printf("dot  : %d\n", specifier.flags & dot_f);
//printf("width: %d\n", specifier.flags & width2_f);
//printf("\nalign: %d\n", specifier.align);
//printf("width: %d\n\n", specifier.width);

static void	ft_print_unsigned(va_list arg, t_spec *specifier)
{
	const t_uint64	number = va_arg(arg, unsigned long long);
	const t_uint8	*base = &(specifier->base);
	//const t_uint8	len = ft_nlen(number, *base);

	if (specifier->type == 'X')
		ft_putnbr_base((t_uint16)number, (*base + upper));
	else if (specifier->type == 'x')
		ft_putnbr_base((t_uint16)number, *base);
	else if (specifier->type == 'p')
		ft_putnbr_base(number, *base);
	else if (specifier->type == 'u')
		ft_putnbr_base((t_uint16)number, *base);
}

static void	ft_print_signed(va_list arg, t_spec *specifier)
{
	const int		number = va_arg(arg, long);
	const char		type = specifier->type;

	if (type == 'd' || type == 'i')
		ft_putnbr_base(number, specifier->base);
	else if (type == 'c' || type == '%')
		write(1, &number, 1);
}

static int	ft_specs_padding(char type, va_list arg, t_spec *specifier)
{
	t_uint8 *base;

	specifier->width -= specifier->precision;
	specifier->type = type;
	base = &(specifier->base);
	*base = (type == 'x' || type == 'X' || type == 'p') ? 16 : 10;
	if (*base == 16 || type == 'u')
		ft_print_unsigned(arg , specifier);
	if (*base == 10 && type != 's')
		ft_print_signed(arg, specifier);
	else if (type == 's')
		ft_putstr_fd(va_arg(arg, char *), 1);
	return (1);
}

static int	ft_flags(char *c, uint8_t *flags, int *width, int *precisn)
{
	const int	size = (ft_isdigit(*c)) ? ft_atoi(c) : 0;

	if (*c == '.')
		*flags += dot_f;
	if (*c == '-')
		*flags += minus_f;
	if (*c == '0')
		*flags += zero_f;
	if (*c == '*' || size)
	{
		*flags += (*flags & width1_f) ? precision2_f : width1_f;
		if (ft_isdigit(*c) && (*flags & dot_f))
			return (ft_nlen((*precisn = size), 10));
		else if (ft_isdigit(*c))
			return (ft_nlen((*width = size), 10));
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
		if ((end = ft_strchr(str, '%')))
		{
			str += write(1, str, end - str);
			end++;
			while (*end && (ft_strchr(FLAGS, *end) || ft_isdigit(*end)))
				end += ft_flags((char *)end, &(s.flags), \
								&(s.width), &(s.precision));
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
	char const *test = "%023.34x\n";
	//char *s = "hi";
	int c = 219837;//'B';
	ft_printf(test, c);
	printf(test, c);
}
