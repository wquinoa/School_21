/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:01:19 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/20 20:28:35 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_uint64		ft_pow(size_t n, size_t pow)
{
	size_t		res;

	res = 1;
	while (pow--)
		res *= n;
	return (res);
}
