/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:34:00 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/06 02:33:20 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	int		l;

	if (!s2)
		return (d = ft_strdup(s1));
	if (!s1)
		return (d = ft_strdup(s2));
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(d = (char *)ft_calloc(l, sizeof(char))))
		return (NULL);
	ft_strlcpy(d, s1, l);
	ft_strlcat(d, s2, l);
	return (d);
}
