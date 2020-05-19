/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:39:39 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/19 16:23:38 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_lltoa_base(int64_t n, uint8_t base)
{
	const char	*neg = (n < 0) ? "-" : NULL;
	char		*result;

	if (base == 10)
	{
		if (n == LLONG_MIN)
			return (ft_strdup("−9223372036854775808"));
		n = (n >= 0) ? : -n;
	}
	return (ft_strjoin(neg, ft_ulltoa_base(n, base)));
}
