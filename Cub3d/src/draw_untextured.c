/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_untextured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:00:42 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/18 15:23:50 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_floor(t_game *g, int x0, int end)
{
	int		y;
	int		col;

	col = g->txr->flr;
	y = g->wnd->height  -1;
	while (y >= 0 && y > end)
	{
		ft_paint(g->frm, x0, y, col);
		if (g->flags & crt_f && !(y % 6))
			col = ft_darken(col, 1);
		y--;
	}
}

void	ft_draw_ceil(t_game *g, int x0, int end)
{
	int		y;
	int		col;

	if (end > g->wnd->height)
		end = g->wnd->height;
	col = g->txr->ceil;
	y = 1;
	while ( y < end)
	{
			ft_paint(g->frm, x0, y, col);
		if (g->flags & crt_f && !(y % 6))
			col = ft_darken(col, 1);
		y++;
	}
}

static int8_t	ft_draw_fisheye(uint16_t ray, float k, t_game *g)
{
	uint16_t		x;
	uint16_t		y;
	const uint32_t	color = ft_calc_color(ray, 1);
	const uint16_t	x0 = g->x0 - g->wnd->width / g->plr->fov * k;

	y = ray + g->wnd->height / FISH;
	x = x0;
	while (y < g->wnd->height - (ray + g->wnd->height / FISH))
		ft_paint(g->frm, x , y++, color);
	x = x0;
	if (g->flags & ref_f)
	while (y++ < g->wnd->height - 2 * ray / 3)
		ft_mix(g->frm, x, y, color);
	return (0);
}

uint8_t	ft_draw_vline(uint16_t ray, float k, t_game *g)
{
	uint16_t		y;
	const uint16_t	x0 = g->x0 - k * g->wnd->width / g->plr->fov;
	const uint32_t	color = ft_calc_color(ray, 0);
	float			halfwall = (HEIGHT >> 1) * g->wnd->height / (ray * cos(k));

	if (g->flags & hal_f)
		return(ft_draw_fisheye(ray, k, g));
	if (halfwall > g->wnd->height >> 1)
		halfwall = g->wnd->height >> 1;
	y = g->y0 - halfwall;
	while (y < g->y0 + halfwall)
		ft_paint(g->frm, x0, y++, color);
	if (!(g->flags & ref_f))
		return (0);
	while (y < g->wnd->height && y < g->y0 + halfwall * 3)
		ft_mix(g->frm, x0, y++, color);
	return(0);
}