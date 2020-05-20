/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:39:39 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 12:37:05 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	ft_is_decimal(t_uint8 base)
{
	return (base & ((1 << 1) | (1 << 3)));
}

char		*ft_lltoa_base(t_int64 n, t_uint8 base)
{
	const char	*neg = (n < 0) ? "-" : NULL;
	char		*result;

	if (ft_is_decimal(base))
	{
		if (n < -LLONG_MAX)
			return (ft_strdup(LLONG_MIN_STR));
		n = (n >= 0) ? : -n;
	}
	return (ft_strjoin(neg, ft_ulltoa_base(n, base)));
}
