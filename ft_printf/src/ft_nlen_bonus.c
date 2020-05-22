/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlen_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:57:33 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/21 17:20:01 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_uint8			ft_nlen(t_uint64 n, t_uint8 base)
{
	t_uint8		i;

	i = (n == 0);
	while (n != 0 && ++i)
		n /= base;
	return (i);
}

t_uint8			ft_nlen_sig(t_int64 n, t_uint8 base)
{
	t_uint8		i;

	i = (n == 0) || (n < 0);
	while (n != 0 && ++i)
		n /= base;
	return (i);
}
