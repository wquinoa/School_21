/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:55:15 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 08:14:20 by wquinoa          ###   ########.fr       */
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
	t_ray p2;
	t_ray pt;

	p2.y = -1;
	g->tex = g->sp;
	g->ray = ((int)item.dist >> 2) * 3;
	while (++p2.y < item.size)
	{
		p2.x = -1;
		if (item.y_off + p2.y < 0 && item.y_off + p2.y > g->wnd->height)
			continue ;
		while (++p2.x < item.size)
		{
			if (item.x_off + p2.x >= 0 && item.x_off + p2.x <
			g->wnd->width && g->depth[item.x_off + (int)p2.x] > item.dist)
			{
				pt.x = p2.x + item.x_off;
				pt.y = p2.y + item.y_off;
				ft_paint_tex(g, pt,
				p2.x * HEIGHT / item.size, p2.y * HEIGHT / item.size);
			}
		}
	}
	g->items++;
	(g->flags & crt_f) ? ft_blend_sprite(item, g, p2.x, p2.y) : 0;
}

void		ft_add_sprite(t_item **items, t_game *g)
{
	t_item		*cur;
	int			i;

	i = -1;
	while (items[++i])
	{
		cur = items[i];
		cur->dist = ft_max(hypot(g->plr->x - cur->x, g->plr->y - cur->y), 32);
		if (cur->dist == 32)
			cur->ex = 0;
		cur->dir = atan2f(cur->y - g->plr->y, cur->x - g->plr->x);
		while (cur->dir - g->plr->dir > M_PI)
			cur->dir -= 2 * M_PI;
		while (cur->dir - g->plr->dir < -M_PI)
			cur->dir += 2 * M_PI;
		cur->size = g->wnd->width / cur->dist * 16;
		cur->x_off = (cur->dir - g->plr->dir) * (g->x0 * 2) / g->plr->fov +
						(g->x0) - (cur->size >> 1);
		cur->y_off = g->y0 - (cur->size >> 1);
	}
	ft_bubble_sort(items);
	while (--i >= 0)
		items[i]->ex ? ft_paint_sprite(*items[i], g) : 0;
}
