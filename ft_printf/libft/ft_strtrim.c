/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:46:16 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/12 12:30:26 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		i;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = 0;
	while (s1[i + 1])
		i++;
	while (i > 0 && ft_strchr(set, s1[i]))
		i--;
	dst = ft_substr(s1, 0, i + 1);
	return (dst);
}
