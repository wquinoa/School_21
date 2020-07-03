/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:13:34 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 08:27:36 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		while (*s && *s != c)
			s++;
		words++;
	}
	return (words);
}

static int	add_words(char **tab, char const *s, char c)
{
	char	*st;
	char	**tmp;
	size_t	i;

	i = 0;
	tmp = NULL;
	tmp = tab;
	while (*s)
	{
		while (*s == c)
			s++;
		st = (char *)s;
		while (*s && *s != c)
			s++;
		i++;
		if (!(*tab++ = ft_substr(st, 0, s - st)))
		{
			ft_tabclear(tmp);
			return (0);
		}
	}
	*tab = NULL;
	return (1);
}

char		**ft_split(char const *s, char c)
{
	size_t	n;
	char	**words;

	if (!s)
		return (NULL);
	n = count_words(s, c);
	if (!(words = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	if (!add_words(words, s, c))
	{
		free(words);
		return (NULL);
	}
	return (words);
}
