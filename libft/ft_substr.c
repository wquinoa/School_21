/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:42:55 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/13 14:29:23 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	size;

	if (!s)
		return (NULL);
	size = (ft_strlen(s + start));
	size = (size > len) ? len : size;
	if (!(d = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(d, &s[start], size + 1);
	return (d);
}
