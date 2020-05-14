/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:13:34 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/14 04:36:18 by wquinoa          ###   ########.fr       */
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
	{
		free(tab[l]);
		tab[l--] = NULL;
	}
	free(tab);
	tab = NULL;
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
			if (!(dst[j] = (char *)malloc((l + 1) * sizeof(char))))
				return (ft_deltab(dst, j));
			while (*s != c && *s)
				dst[j][i++] = *(s++);
			dst[j][i] = '\0';
		}
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

char			**ft_split(char const *s, char c)
{
	int		wrds;
	char	*str;
	char	**dst;

	if (!s || !(str = ft_strtrim(s, &c)))
		return (NULL);
	if (!(wrds = ft_countw(str, c, 0)))
	{
		free(str);
		return (NULL);
	}
	if (!(dst = (char **)malloc((wrds + 1) * sizeof(char *))))
		return (NULL);
	return (ft_realsplit(str, c, dst, wrds));
}
