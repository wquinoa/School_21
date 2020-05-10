/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:13:34 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/11 02:15:23 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countw(char const *s, char c, int words)
{
	int is_word;

	is_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!is_word)
				words++;
			is_word = 1;
		}
		else
			is_word = 0;
		s++;
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

static void		ft_deltab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab);
}

static char		**ft_realsplit(char const *s, char c, char **dst)
{
	int		i;
	int		j;
	int		l;

	j = 0;
	while (*s)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		l = ft_len(s, c) + 1;
		if (!(dst[j] = (char *)ft_calloc(l, sizeof(char))))
		{
			ft_deltab(dst);
			return (NULL);
		}
		while (*s != c && *s)
			dst[j][i++] = *(s++);
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
	if (!(dst = (char **)ft_calloc(l + 1, sizeof(char *))))
		return (NULL);
	return (ft_realsplit(str, c, dst));
}
