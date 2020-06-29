/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:55:15 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/29 20:51:48 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_bubble_sort(t_item **array)
{
	uint16_t	passes;
	t_item		*tmp;
	uint16_t	i;

	i = -1;
	passes = 0;
	while (array[++i])
		passes++;
	while (--passes)
	{
		i = -1;
		while (++i < passes)
		{
			if (array[i]->dist > array[i + 1]->dist)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	}
}

static void	ft_blend_sprite(t_item item, t_game *g, short x, short y)
{
	t_ray pt;

	y = -1;
	item.y_off += item.size * 2;
	while (++y < item.size)
	{
		x = -1;
		if (item.y_off + y < 0 && item.y_off + y > (short)g->wnd->height)
			continue ;
		while (++x < item.size)
		{
			if (item.x_off + x >= 0 && item.x_off + x < (short)g->wnd->width
								&& g->depth[item.x_off + x] > item.dist)
			{
				pt.x = x + item.x_off;
				pt.y = y + item.y_off;
				ft_blend_tex(g, pt,
				x * HEIGHT / item.size, y * HEIGHT / item.size);
			}
		}
	}
}

static void	ft_paint_sprite(t_item item, t_game *g)
{
	short y;
	short x;
	t_ray pt;

	y = -1;
	g->tex = g->sp;
	while (++y < item.size)
	{
		x = -1;
		if (item.y_off + y < 0 && item.y_off + y > (short)g->wnd->height)
			continue ;
		while (++x < item.size)
		{
			if (item.x_off + x >= 0 && item.x_off + x < (short)g->wnd->width
								&& g->depth[item.x_off + x] > item.dist)
			{
				pt.x = x + item.x_off;
				pt.y = y + item.y_off;
				ft_paint_tex(g, pt,
				x * HEIGHT / item.size, y * HEIGHT / item.size);
			}
		}
	}
	if (g->flags & crt_f)
		ft_blend_sprite(item, g, x, y);
}

void		ft_add_sprite(t_item **items, t_game *g)
{
	t_item		*curr;
	int			i;

	i = -1;
	while (items[++i])
	{
		curr = items[i];
		curr->dist = ft_max(hypot(g->plr->x - curr->x, g->plr->y - curr->y), 24);
		if (curr->dist == 24)
			curr->ex = 0;
		curr->dir = atan2f(curr->y - g->plr->y, curr->x - g->plr->x);
		while (curr->dir - g->plr->dir > M_PI)
			curr->dir -= 2 * M_PI;
		while (curr->dir - g->plr->dir < -M_PI)
			curr->dir += 2 * M_PI;
		curr->size = g->wnd->width / curr->dist * 16;
		curr->x_off = (curr->dir - g->plr->dir) * (g->x0 * 2) / g->plr->fov +
						(g->x0) - (curr->size >> 1);
		curr->y_off = g->y0 - (curr->size >> 1);
	}
	ft_bubble_sort(items);
	while (--i >= 0)
		items[i]->ex ? ft_paint_sprite(*items[i], g) : 0;
}
