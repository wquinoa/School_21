/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:01:19 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/14 04:40:03 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int n, int pow)
{
	int			res;

	if (pow == 0 || n == 1)
		return (1);
	if (pow < 0)
		return (-1);
	res = 1;
	while (pow--)
	{
		if ((int)ft_abs(res * n) / n != (int)ft_abs(n))
			return (-1);
		res *= n;
	}
	return (res);
}
