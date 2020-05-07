/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:11:16 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/07 21:28:47 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_join(char **tab, char *dlm)
{
	char	*tmp;
	char	*res;
	int		i;

	if (!tab || !*tab || !dlm)
		return (NULL);
	if (!(res = ft_strdup(*tab)))
		return (NULL);
	i = 0;
	while (++i && tab[i])
	{
		if (!(tmp = ft_strjoin_dlm(res, dlm, tab[i])))
		{
			free(res);
			return (NULL);
		}
		if (!(res = ft_strdup(tmp)))
		{
			free(tmp);
			return (NULL);
		}
	}
	free(tmp);
	return (res);
}
