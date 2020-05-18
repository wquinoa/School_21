/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 15:58:46 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/18 09:29:01 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
		while (*s)
			s++;
	else
		while (*s != (char)c && *s)
			s++;
	return ((*s == (char)c || c == '\0') ? (char *)s : NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const size_t l = ft_strchr(src, '\0') - src;

	while ((dstsize--) - 1 && *src)
		*(dst++) = *(src++);
	*dst = '\0';
	return (l);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const size_t	ldst = ft_strchr(dst, '\0') - dst;
	const size_t	lsrc = ft_strchr(src, '\0') - src;

	if (dstsize > ldst)
	{
		while (*dst)
			dst++;
		ft_strlcpy(dst, src, dstsize);
	}
	return (lsrc + ((dstsize > ldst) ? ldst : dstsize));
}

char	*ft_strdup(const char *s)
{
	const	size_t l = ft_strchr(s, '\0') - s;
	char	*dst;

	if (!(dst = (char *)malloc((l + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(dst, s, l + 1);
	return (dst);
}
