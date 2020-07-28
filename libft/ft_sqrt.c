/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:31:27 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/13 07:54:29 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_sqrt(size_t n)
{
	size_t	tmp;
	size_t	res;

	if (n == 1 || n == 0)
		return (1);
	tmp = 0;
	res = n / 2;
	while (res != tmp)
	{
		tmp = res;
		res = (n / tmp + tmp) / 2;
	}
	return (res * res == n ? res : 0);
}
