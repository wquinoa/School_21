/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:28:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 16:03:28 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_item	**ft_itemtab(t_item *ilist, uint8_t amt)
{
	t_item		**items;
	int			i;

	if (!amt)
		return (NULL);
	if (!(items = (t_item**)malloc(sizeof(t_item *) * (amt + 1))))
		ft_errors(bad_malloc);
	i = -1;
	while (++i < amt)
	{
		items[i] = ilist;
		ilist = ilist->next;
	}
	items[i] = NULL;
	return (items);
}

static int		ft_init_item(uint16_t x, uint16_t y, t_item **items)
{
	t_item	*tmp;
	t_item	*new;

	if (!(new = (t_item*)malloc(sizeof(t_item))))
		ft_errors(bad_malloc);
	tmp = *items;
	ft_bzero(new, sizeof(t_item));
	new->x = x * HEIGHT + (HEIGHT >> 1);
	new->y = y * HEIGHT + (HEIGHT >> 1);
	new->ex = 1;
	if (!(*items))
		*items = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_item			**ft_init_sprites(char **map)
{
	uint16_t	x;
	uint16_t	y;
	uint8_t		amt;
	t_item		*ilist;

	y = -1;
	amt = 0;
	ilist = NULL;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '2')
			{
				amt += ft_init_item(x, y, &ilist);
				map[y][x] = '0';
			}
		}
	}
	return (ft_itemtab(ilist, amt));
}
