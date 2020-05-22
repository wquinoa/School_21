/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 13:19:17 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/22 15:25:22 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int			ft_toupper(int c)
{
	return (c -= ('a' <= c && c <= 'z') * 32);
}

int			ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t		ft_strlen(char const *s)
{
	const char *start = s;

	while (*s)
		s++;
	return (s - start);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s)
		s++;
	return (*s == (char)c ? (char *)s : NULL);
}
