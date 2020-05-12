/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 19:53:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/11 14:59:50 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_space(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int						ft_atoi(const char *str)
{
	long long int			res;
	int						fac;
	int						sgn;
	int						i;

	fac = 1;
	res = 0;
	i = 0;
	while (*str && ft_space(*str))
		str++;
	sgn = (*str == '-') ? -1 : 1;
	str += (*str == '-' || *str == '+');
	while (ft_isdigit(str[i]))
		i++;
	while (--i >= 0 && ft_isdigit(str[i]))
	{
		res += (str[i] - '0') * fac * sgn;
		if ((sgn > 0) != (res > 0) && res)
			return (sgn == 1 ? -1 : 0);
		fac *= 10;
	}
	return (res);
}
