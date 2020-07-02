/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_untextured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:00:42 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 03:19:39 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_darken(int color, int16_t i)
{
	if (i > 255)
		i = 255;
	return (color -= (
	(i << 16) * ((color & red) > (255 - i)) |
	(i << 8) * ((color & grn) > (255 - i)) |
	(i << 0) * ((color & blu) > (255 - i))));
}

void	ft_draw_floor(t_game *g, int x, int end)
{
	int		y;
	int		col;

	col = g->txr->flr;
	y = g->wnd->height - 1;
	while (y >= 0 && y > end)
	{
		ft_paint(g->frm, x, y, col);
		if ((g->flags & crt_f) && !(y & 5))
			col = ft_darken(col, 1);
		y--;
	}
}

void	ft_draw_ceil(t_game *g, int x, int end)
{
	int		y;
	int		col;

	if (end > (int)g->wnd->height)
		end = g->wnd->height;
	col = g->txr->ceil;
	y = 1;
	while (y < end)
	{
		ft_paint(g->frm, x, y, col);
		if ((g->flags & crt_f) && !(y & 2))
			col = ft_darken(col, 1);
		y++;
	}
}
