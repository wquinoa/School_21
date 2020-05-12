/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:13:34 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/12 16:13:07 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countw(char const *s, char c, int words)
{
	while (*s)
	{
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
		words++;
	}
	return (words);
}

static int		ft_len(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void		*ft_deltab(char **tab, int l)
{
	if (!*tab)
		return (NULL);
	while (l >= 0)
		free(tab[l--]);
	free(tab);
	return (NULL);
}

static char		**ft_realsplit(char *s, char c, char **dst, int words)
{
	int		i;
	int		j;
	int		l;

	j = 0;
	while (j < words)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			l = ft_len(s, c);
			if (!(dst[j] = (char *)ft_calloc(l + 1, sizeof(char))))
				return (ft_deltab(dst, j));
			while (*s != c && *s)
				dst[j][i++] = *(s++);
		}
		j++;
	}
	return (dst);
}

char			**ft_split(char const *s, char c)
{
	int		l;
	char	*str;
	char	**dst;

	if (!s || !(str = ft_strtrim(s, &c)))
		return (NULL);
	l = ft_countw(str, c, 0);
	if (!(dst = (char **)malloc((l + 1) * sizeof(char *))))
		return (NULL);
	return (ft_realsplit(str, c, dst, l));
}
