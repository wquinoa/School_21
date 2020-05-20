/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:06:59 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 13:12:01 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_ulltoa_base(uint64_t n, uint8_t base)
{
	const uint8_t	len = ft_nlen(n, (base &= ~upper));
	uint64_t		div;
	uint8_t			num;
	char			*result;

	if (!(result = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	result[len] = '\0';
	div = ft_pow(base, len - 1);
	while (div != 0)
	{
		result[num++] = BASE[n / div];
		n %= div;
		div /= base;
	}
	return (result);
}
