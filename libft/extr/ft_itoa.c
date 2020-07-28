/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 19:54:53 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/07 05:36:20 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_numlen(int n)
{
	int				i;

	i = 0;
	if (n >= 0 && n <= 9)
		return (1);
	while (n != 0 && ++i)
		n /= 10;
	return (i);
}

static char			*ft_ltoa(char *s, long int m)
{
	long int		d;
	int				i;

	d = 10000000000;
	i = (m < 0);
	if (m < 0)
	{
		s[0] = '-';
		m = -m;
	}
	while (d > m)
		d /= 10;
	while (d >= 10)
	{
		s[i] = (m / d) + '0';
		m %= d;
		d /= 10;
		i++;
	}
	s[i] = m + '0';
	s[i + 1] = '\0';
	return (s);
}

char				*ft_itoa(int n)
{
	long int		m;
	int				l;
	char			*s;

	m = (long int)n;
	l = (n < 0) + ft_numlen(n);
	n *= (n < 0) ? -1 : 1;
	if (!(s = (char *)ft_calloc(l + 1, sizeof(char))))
		return (NULL);
	return (ft_ltoa(s, m));
}
