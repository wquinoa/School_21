/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/26 10:22:00 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

static void		ft_clear_struct(t_spec *specifier)
{
	specifier->base = 0;
	specifier->flags = 0;
	specifier->precision = 0;
	specifier->type = 0;
	specifier->width = 0;
}

static int		ft_flags(char *c, t_spec *s, va_list arg)
{
	int size;

	size = 0;
	if (ft_isdigit(*c) || *c == '*')
	{
		if (!s->flags && *c == '0')
			s->flags |= zero_f;
		size = (*c == '*') ? va_arg(arg, int) : ft_atoi(c);
		if (!(s->flags & dot_f))
			s->width = size;
		if (s->width < 0)
		{
			s->width *= -1 * (s->width < 0);
			s->flags |= minus_f;
		}
		s->precision = size * ((s->flags & dot_f) > 0);
		return ((*c == '*') ? 1 : ft_nlen(ft_abs(size), 10));
	}
	if (*c == '-' && !s->flags)
		s->flags |= minus_f;
	if (*c == '.' && (*(c + 1) != '-'))
		s->flags |= dot_f;
	return (1);
}

int				ft_printf(const char *str, ...)
{
	const char		*end = str;
	static t_spec	s;
	va_list			ap;

	if (!str)
		return(-1);
	s.length = ft_strlen(str);
	va_start(ap, str);
	while (*str)
	{
		ft_clear_struct(&s);
		if ((end = ft_strchr(str, '%')))
		{
			str += write(1, str, (end++) - str);
			while (*end && (ft_strchr(FLAGS, *end) || ft_isdigit(*end)))
				end += ft_flags((char *)end, &(s), ap);
			end += ft_define_type(*end, ap, &s);
			s.length -= (end - str);
			str = end;
		}
		else
			str += write(1, str, ft_strlen(str));
	}
	va_end(ap);
	return (s.length);
}
