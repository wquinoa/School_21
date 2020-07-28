/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 01:23:29 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/03 02:04:35 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t nlen;

	if (!*needle)
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	while (*haystack && len > 0)
	{
		if (*haystack == *needle)
			if (ft_memcmp(haystack, needle, nlen) == 0 && len >= nlen)
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
