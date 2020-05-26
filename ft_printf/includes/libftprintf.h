/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 14:05:37 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/24 21:27:59 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# define INT_MAX 2147483647
# define LLONG_MAX 9223372036854775807LL
# define LLONG_MIN_STR "9223372036854775808"
# define BASE "0123456789abcdef"
# define SPECS "%csuxXpdi"
# define FLAGS "-.0*# +"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

/*
**	# define FLT_MAX 3.402823e+38
**
**						0 0 0 0 0 0 0 1 << 3
**						0 0 0 0 1 0 0 0 == 8
**
**	specifier->flags |= width1;		sets flag for width. Mostly using += though.
**	specifier->flags &= ~width1;	cancels that flag
**	specifier->flags & width1		checks whether it is set (width == 1)
**	specifier->flags = 0			unsets all the flags (resets them to zero)
*/

enum						e_flag
{
	zero_f = (1 << 0),
	minus_f = (1 << 1),
	width1_f = (1 << 2),
	dot_f = (1 << 3),
	precision2_f = (1 << 4),
	base_bits = 0x1F,
	upper = (1 << 5),
	is_neg = (1 << 6),
	hex = (1 << 7),
	z_and_m = zero_f + minus_f
};

typedef unsigned char		t_uint8;
typedef unsigned int		t_uint32;
typedef unsigned long long	t_uint64;
typedef long long			t_int64;

typedef struct				s_spec
{
	t_uint8					type;
	t_uint8					base;
	t_uint8					flags;
	int						width;
	int						precision;
	size_t					length;
}							t_spec;

/*
**	Math (ft_math.c)
*/

int							ft_max(int a, int b);
int							ft_min(int a, int b);
t_int64						ft_abs(t_int64 n);
int							ft_atoi(const char *str);
t_uint8						ft_nlen(t_uint64 n, t_uint8 base);
t_uint64					ft_pow(size_t n, size_t pow);

/*
**	String manipulation and printing (ft_putnbr_base.c, ft_print.c, ft_string.c)
*/

int							ft_printf(const char *str, ...);
int							ft_define_type(const char type, va_list arg, \
															t_spec *spcfier);
void						ft_pad(char p_type, int len, t_spec *specifier);
void						ft_putnbr_base(t_int64 n, t_uint8 base, t_spec *s);
void						ft_putull_base(t_uint64 n, t_uint8 base, t_spec *s);
char						*ft_strchr(const char *s, int c);
size_t						ft_strlen(char const *s);
int							ft_isdigit(int c);
int							ft_toupper(int c);

#endif
