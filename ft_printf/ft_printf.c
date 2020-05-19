/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 00:59:21 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "src/libftprintf.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

//			printf("minus: %d\n", specifier.flags & minus_f);
			//printf("zero : %d\n", specifier.flags & zero_f);
			//printf("jstfy: %d\n", specifier.flags & jstfy1_f);
			//printf("dot  : %d\n", specifier.flags & dot_f);
			//printf("width: %d\n", specifier.flags & width2_f);
			//printf("jstfy: %d\n", specifier.jstfy);
			//printf("width: %d\n", specifier.width);

/*
** • The prototype of ft_printf should be int ft_printf(const char *, ...);
** • You have to recode the libc’s printf function
** • It must not do the buffer management like the real printf
** • It will manage the following conversions: cspdiuxX%
** • It will manage any combination of the following flags: ’-0.*’ and minimum field
**   width with all conversions
** • It will be compared with the real printf
*/

static void	ft_specs(char c, va_list arg)
{
	if (c == 's')
		ft_putstr_fd(va_arg(arg, char *), 1);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'c')
		ft_putchar_fd(va_arg(arg, int), 1);
	else if (c == 'x')
		ft_putnbr_base(va_arg(arg, unsigned long long), 16);
	else if (c == 'p')
		ft_putnbr_base(va_arg(arg, unsigned long long), 16);
	else if (c == 'u')
		ft_putnbr_base(va_arg(arg, unsigned int), 10);
	else if (c == '%')
		ft_putchar_fd('%', 1);
}

int		ft_flags(const char *c, t_spec *spec)
{
	if (*c == '-')
		spec->flags += minus_f;
	if (*c == '0')
		spec->flags += zero_f;
	else if (*c == '*' || (*c != '0' && ft_isdigit(*c)))
	{
		if (!(spec->flags & jstfy1_f))
		{
			spec->flags |= jstfy1_f;
			if (ft_isdigit(*c))
			{
				spec->jstfy = ft_atoi(c);
				return(ft_nlen(spec->jstfy, 10));
			}
		}
		else if (!(spec->flags & width2_f))
		{
			spec->flags |= width2_f;
			if (ft_isdigit(*c))
			{
				spec->width = ft_atoi(c);
				return(ft_nlen(spec->width, 10));
			}
		}
	}
	if (*c == '.')
		spec->flags += dot_f;
	if (*c == '%')
		spec->flags += prcnt_f;
	return (1);
}

int		ft_printf(const char *str, ...)
{
	const char		*start = str;
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
				end += ft_flags(end, &specifier);
			if (ft_strchr(SPECS, *end))
			{
				ft_specs(*end, ap);
				end++;
				str = end;
			}
		}
		str += write(1, str, ft_strlen(str));
	}
	va_end(ap);
	return (0);
}

int main(void)
{
	char const *test = "hello there, %-14.15d% friend\n";
	char *s = "hi";
	int c = -219837;//'B';
	ft_printf(test, c);
	//printf(test, c);
}