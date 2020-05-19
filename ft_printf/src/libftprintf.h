/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 14:05:37 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/19 23:24:21 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# define SPECS "cspdiuxX"
# define FLAGS "-.0*"
//# define ADD_FLAG specifier->flag +=
# define DEBUG write(1, "\033[32mcycle\n\033[0m", 17);
# include "../libft/libft.h"

/*
** • The prototype of ft_printf should be int ft_printf(const char *, ...);
** • You have to recode the libc’s printf function
** • It must not do the buffer management like the real printf
** • It will manage the following conversions: cspdiuxX%
** • It will manage any combination of the following flags: ’-0.*’ and minimum field
**   width with all conversions
** • It will be compared with the real printf
*/

enum				e_flag
{
	minus_f = (1 << 0),
	zero_f = (1 << 1),
	jstfy1_f = (1 << 2),
	dot_f = (1 << 3),
	width2_f = (1 << 4),
	prcnt_f = (1 << 5),
};

/*
**	specifier->flags |= ast1;		sets flag for asterisk1
**	specifier->flags &= ~ast1;		cancels that flag
**	specifier->flags & ast1			checks whether it is set
**	int flags += (minus + width)	sets the required flags!!!
**	specifier->flags = 0			obviously unsets all of the flags (resets them to zero)
*/

typedef struct		s_spec
{
	char			type;
	uint8_t			flags;
	int				jstfy;
	int				width;
}					t_spec;

char				*ft_lltoa_base(int64_t n, uint8_t base);
char				*ft_ulltoa_base(uint64_t n, uint8_t base);

#endif
