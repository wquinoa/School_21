/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 08:05:53 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/17 15:18:54 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabclear(char **tab)
{
	int		i;

	if (!tab)
		return ;
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
	tab = NULL;
}
