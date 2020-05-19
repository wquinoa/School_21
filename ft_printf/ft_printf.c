/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/19 23:41:22 by wquinoa          ###   ########.fr       */
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
}

int		ft_flags(const char *c, t_spec *specifier)
{
	t_spec	*curr_flags;

	curr_flags->flags = specifier->flags;
	if (*c == '-')
		curr_flags->flags |= minus_f;
	if (specifier->flags)
	{
		printf("minus: %d\n", specifier->flags & minus_f);
		printf("zero : %d\n", specifier->flags & zero_f);
		printf("jstfy: %d\n", specifier->flags & jstfy1_f);
		printf("dot  : %d\n", specifier->flags & dot_f);
		printf("width: %d\n", specifier->flags & width2_f);
		printf("prcnt: %d\n", specifier->flags & prcnt_f);
	}
	if (*c == '0')
		*curr_flags |= zero_f;
	else if (*c == '*' || (ft_isdigit(*c)))
	{
		if (!(*curr_flags & jstfy1_f))
			specifier->width = ft_atoi(c);
		else
			specifier->jstfy = ft_atoi(c);
		*curr_flags |= (*curr_flags & jstfy1_f) ? jstfy1_f : width2_f;
		return ((*curr_flags & jstfy1_f) ? ft_nlen(specifier->jstfy, 10) : ft_nlen(specifier->width, 10));
	}
	if (*c == '.')
		*curr_flags += dot_f;
	if (*c == '%')
		*curr_flags |= prcnt_f;
	return (1);
}

int		ft_printf(const char *str, ...)
{
	const char		*start = str;
	const char		*end = str;
	va_list			ap;
	static t_spec	specifier;

	va_start(ap, str);
	while (*str)
	{
		if ((end = ft_strchr(str, '%')))
		{
			str += write(1, str, end - str);
			end++;
			while (*end && (ft_strchr(FLAGS, *end || ft_isdigit(*end))))
			{
				end += ft_flags(end, &specifier);
				if (specifier.flags)
				{
					printf("minus: %d\n", specifier.flags & minus_f);
					printf("zero : %d\n", specifier.flags & zero_f);
					printf("jstfy: %d\n", specifier.flags & jstfy1_f);
					printf("dot  : %d\n", specifier.flags & dot_f);
					printf("width: %d\n", specifier.flags & width2_f);
					printf("prcnt: %d\n", specifier.flags & prcnt_f);
				}
			}
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
	char const *test = "hello there, %-0*.*d% friend\n";
	char *s = "hi";
	int c = -219837;//'B';
	ft_printf(test, c);
	//printf(test, c);
}