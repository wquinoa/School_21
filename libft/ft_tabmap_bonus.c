/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 08:25:33 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/29 16:46:33 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabmap(char **tab, char *(*f)(const char *))
{
	char	**res;
	int		len;
	int		l;
	int		i;

	if (!tab || !f)
		return (NULL);
	len = ft_tablen(tab);
	if (!(res = (char **)malloc((sizeof(char *) * (len + 1)))))
		return (NULL);
	i = -1;
	while (++i < len)
	{
		l = ft_strlen(tab[i]);
		res[i] = (char *)ft_calloc(l + 1, sizeof(char));
		if (!(res[i]))
		{
			ft_tabclear(res);
			return (NULL);
		}
		res[i] = ft_strdup(tab[i]);
	}
	res[i] = NULL;
	return (res);
}
