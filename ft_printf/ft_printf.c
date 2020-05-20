/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 05:29:29 by wquinoa          ###   ########.fr       */
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
*/

//printf("\nminus: %d\n", specifier.flags & minus_f);
//printf("zero : %d\n", specifier.flags & zero_f);
//printf("align: %d\n", specifier.flags & align1_f);
//printf("dot  : %d\n", specifier.flags & dot_f);
//printf("width: %d\n", specifier.flags & width2_f);
//printf("\nalign: %d\n", specifier.align);
//printf("width: %d\n\n", specifier.width);

static int			ft_specs(char c, va_list arg)
{
	if (c == 's')
		ft_putstr_fd(va_arg(arg, char *), 1);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'c')
		ft_putchar_fd(va_arg(arg, int), 1);
	else if (c == 'x')
		ft_putnbr_base(va_arg(arg, unsigned long long), 16);
	else if (c == 'X')
		ft_putnbr_base(va_arg(arg, unsigned long long), (16 + upper));
	else if (c == 'p')
	{
		write(1, "0x", 2);
		ft_putnbr_base(va_arg(arg, unsigned long long), 16);
	}
	else if (c == 'u')
		ft_putnbr_base(va_arg(arg, unsigned int), 10);
	else if (c == '%')
		ft_putchar_fd('%', 1);
	return (1);
}

static int			ft_flags(const char *c, uint8_t *flags,
									int *align, int *width)
{
	const int	size = (ft_isdigit(*c) * (*c > '0')) ? ft_atoi(c) : 0;

	if (*c == '.')
		*flags += dot_f;
	if (*c == '0' || *c == '-')
		*flags += (*c == '0') ? zero_f : minus_f;
	if (*c == '*' || size)
	{
		*flags += (*flags & align1_f) ? width2_f : align1_f;
		if (ft_isdigit(*c) && (*flags & dot_f))
			return (ft_nlen((*width = size), 10));
		else if (ft_isdigit(*c))
			return (ft_nlen((*align = size), 10));
		return ((*align) ? ft_nlen(*align, 10) : ft_nlen(*width, 10));
	}
	return (1);
}

int		ft_printf(const char *str, ...)
{
	const char		*end = str;
	static t_spec	specifier;
	va_list			ap;

	va_start(ap, str);
	while (*str)
	{
		if ((end = ft_strchr(str, '%')))
		{
			str += write(1, str, end - str);
			end++;
			while (*end && (ft_strchr(FLAGS, *end) || ft_isdigit(*end)))
				end += ft_flags(end, &(specifier.flags),
				&(specifier.align), &(specifier.width));
			if (ft_strchr(SPECS, *end))
			{
				end += ft_specs(*end, ap);
				str = end;
			}
		}
		else
			str += write(1, str, ft_strlen(str));
	}
	va_end(ap);
	return (0);
}

int main(void)
{
	char const *test = "hello there, %-129837.34615X %-s\n";
	char *s = "hi";
	int c = -219837;//'B';
	ft_printf(test, c, s);
	//printf(test, c);
}
