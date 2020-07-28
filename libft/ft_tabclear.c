/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 08:05:53 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/16 23:38:14 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabclear(char **tab)
{
	int		i;

	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	}
	free(tab);
	return (NULL);
}
