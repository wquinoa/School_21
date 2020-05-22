/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 14:05:37 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/22 00:30:04 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# define LLONG_MIN -9223372036854775807LL
# define LLONG_MIN_STR "−9223372036854775808"
# define BASE "0123456789abcdef"
# define SPECS "%csuxXpdi"
# define FLAGS "-.0*# +"
# define DEBUG write(1, "\033[32mboop\n\033[0m", 17);
# include "../libft/libft.h"

/*
**	0 0 0 0 0 0 0 1 << 3
**	0 0 0 0 1 0 0 0 == 8
**
**	specifier->flags |= width1;		sets flag for asterisk. Using += for readability
**	specifier->flags &= ~width1;	cancels that flag
**	specifier->flags & width1		checks whether it is set (width == 1)
**	specifier->flags = 0			obviously unsets all of the flags (resets them to zero)
*/

enum						e_flag
{
	width1_f = (1 << 2),
	dot_f = (1 << 3),
	precision2_f = (1 << 4),
	base_bits = 0x1F,
	is_neg = (1 << 6),
	hex = (1 << 7),
	upper = (1 << 5),
	zero_f = (1 << 0),
	minus_f = (1 << 1),
	z_and_m = zero_f + minus_f
};

typedef unsigned char		t_uint8;
typedef unsigned int		t_uint16;
typedef unsigned long long	t_uint64;
typedef long long			t_int64;

typedef struct				s_spec
{
	t_uint8					type;
	t_uint8					base;
	t_uint8					flags;
	t_uint8					length;
	int						width;
	int						precision;
}							t_spec;

int							ft_max(int a, int b);
t_uint8						ft_nlen(t_uint64 n, t_uint8 base);
t_uint8						ft_nlen_sig(t_int64 n, t_uint8 base);
t_uint64					ft_pow(size_t n, size_t pow);
void						ft_pad(char p_type, int len);//, t_uint8 base);
void						ft_putnbr_base(int64_t n, uint8_t base, t_spec *s);
void						ft_putull_base(uint64_t n, uint8_t base, t_spec *s);

#endif
