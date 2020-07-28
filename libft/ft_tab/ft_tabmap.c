/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 08:25:33 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/20 17:16:30 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabmap(char **tab, char *(*f)(const char *))
{
	char	**res;
	int		len;
	int		i;

	if (!tab || !f)
		return (NULL);
	len = ft_tablen(tab);
	if (!(res = (char **)malloc((sizeof(char *) * (len + 1)))))
		return (NULL);
	i = -1;
	while (++i < len)
	{
		res[i] = f(tab[i]);
		if (!(res[i]))
			return (ft_tabclear(res));
	}
	res[i] = NULL;
	return (res);
}
