/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:49:16 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 02:33:00 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strswap(char *str, char from, char to)
{
	char *res;

	res = str;
	while (*str)
	{
		if (*str == from)
			*str = to;
		str++;
	}
	return (res);
}
