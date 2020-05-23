/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:55:36 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/23 12:44:42 by wquinoa          ###   ########.fr       */
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

static void		is_it_dot(t_spec *s, int size)
{
	if (s->flags & dot_f)
		s->precision = size;
	else
		s->width = ft_abs(size);
}

static int		ft_flags(char *c, t_spec *s, va_list arg)
{
	int	size;

	size = (ft_isdigit(*c)) ? ft_atoi(c) : 0;
	if (*c == '.')
		s->flags += dot_f;
	if (*c == '-')
		s->flags += minus_f;
	if (*c == '0')
		s->flags += zero_f * ((s->flags & minus_f) == 0);
	if (*c == '*' || size)
	{
		if (*c == '*')
			size = va_arg(arg, int);
		s->flags += (s->flags & dot_f) ? precision2_f : width1_f;
		s->flags |= minus_f * ((size < 0) && !(s->flags & dot_f));
		is_it_dot(s, size);
		if (*c == '*')
		{
			va_end(arg);
			return (1);
		}
		return ((s->flags & dot_f) ? \
				ft_nlen(s->precision, 10) : ft_nlen(s->width, 10));
	}
	return (1);
}

int				ft_printf(const char *str, ...)
{
	const char		*end = str;
	static t_spec	s;
	va_list			ap;

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
