/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:11:16 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/12 06:59:55 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_del(void *content)
{
	free(content);
	return (NULL);
}

char		*ft_join(char **tab, char *dlm)
{
	char	*tmp;
	char	*res;
	int		i;

	if (!tab || !dlm || !(res = ft_strdup(*tab)))
		return (NULL);
	i = 0;
	tmp = NULL;
	while (++i && tab[i])
	{
		if (!(tmp = ft_strjoin_dlm(res, dlm, tab[i])))
			return (ft_del(res));
		if (!(res = ft_strdup(tmp)))
			return (ft_del(tmp));
	}
	free(tmp);
	return (res);
}
