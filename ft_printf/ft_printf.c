/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/15 17:42:35 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <string.h>
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

void	ft_switch(char c, va_list arg)
{
	if (c == 's')
		ft_putstr_fd(va_arg(arg, char *), 1);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(arg, int), 1);
	else if (c == 'c')
		ft_putchar_fd(va_arg(arg, int), 1);
}

int		ft_printf(const char *str, ...)
{
	va_list ap;
	int d;
	char *s, c;
	ft_putendl_fd(str, 1);

	va_start(ap, str);
	while(*str)
	{
		if(*str == '%' && *(str + 1))
		{
			str++;
			ft_switch(*str, ap);
			va_end(ap);
			str++;
		}
		else
			ft_putchar_fd(*(str++), 1);
	}
	va_end(ap);
	return(0);
}

int main()

{

	ft_printf("abcde %s %ilaskdj\n", "toto", 12323);
}
