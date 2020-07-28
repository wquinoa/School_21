/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 22:46:47 by jalvaro           #+#    #+#             */
/*   Updated: 2020/07/24 21:15:03 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free_array(char **arr, size_t index)
{
	size_t i;

	i = 0;
	while (i < index)
		free(arr[i++]);
	free(arr);
	return (0);
}

static size_t	ft_counter(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if ((s[i] == c) || (s[i] == '\0' && s[i - 1] != c))
			size++;
	}
	return (size);
}

static char		**ft_str_filler(char const *s, char **str, char c, size_t size)
{
	size_t	k;
	size_t	i;
	size_t	start;

	i = 0;
	k = 0;
	start = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			start = ++i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if ((s[i] == c) || (s[i] == '\0' && s[i - 1] != c))
		{
			if (!(str[k++] = ft_substr(s, start, (i - start))))
				return (ft_free_array(str, size));
		}
	}
	return (str);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	size_t	size;

	if (!s)
		return (0);
	size = ft_counter(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (size + 1))))
		return (0);
	str[size] = 0;
	return (ft_str_filler(s, str, c, size));
}
