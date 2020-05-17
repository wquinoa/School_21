/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 08:05:53 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/07 08:18:30 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabclear(char **tab, int len)
{
	int		i;

	if (!tab)
		return ;
	i = -1;
	while (++i < len)
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
