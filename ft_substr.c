/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:42:55 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/04 19:34:32 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (!(d = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (i < len && s[start + i])
	{
		d[i] = s[start + i];
		i++;
	}
	return (d);
}
