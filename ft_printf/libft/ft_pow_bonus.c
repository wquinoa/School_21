/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:01:19 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/13 09:08:57 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int n, int pow)
{
	int			res;

	if (pow <= 0 || n == 1)
		return (1);
	res = 1;
	while (pow--)
	{
		if ((int)ft_abs(res * n) < (int)ft_abs(n))
			return ((n > 0) ? -1 : 0);
		res *= n;
	}
	return (res);
}

int main()
{
	ft_putnbr_fd(ft_pow(10, 2), 1);
}