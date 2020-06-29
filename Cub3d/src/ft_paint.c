/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:15:59 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/25 15:13:57 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_blend(int fg, int bg, uint16_t amount)
{
	int r;
	int g;
	int b;

	r = (((fg & red) >> 16) / 64 * amount) +
	(((bg & red) >> 16) / 64 * (64 - amount));
	g = (((fg & grn) >> 8) / 64 * amount) +
	(((bg & grn) >> 8) / 64 * (64 - amount));
	b = (((fg & blu) >> 0) / 64 * amount) +
	(((bg & blu) >> 0) / 64 * (64 - amount));
	return (((r << 16) & red) | ((g << 8) & grn) | (b & blu));
}

void		ft_paint(t_frame *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_l + x * (f->bpp >> 3));
	*(int *)dst = color;
}

void		ft_blend_tex(t_game *g, t_ray pt, int offset, int i)
{
	char	*win;
	char	*tex;
	int		color;

	if (pt.y >= 0 && pt.y < (int)g->wnd->height)
	{
		tex = g->tex->addr + (int)((HEIGHT - i - 1) * g->tex->line_l +
			offset * (g->tex->bpp >> 3));
		if (*(int*)tex == 0x010101)
			return ;
		win = g->frm->addr + ((int)pt.y * g->frm->line_l +
			(int)pt.x * (g->frm->bpp >> 3));
		color = ft_blend(g->txr->flr, *((int*)tex),
				(i < 56) ? (36 + i / 2) : 64);
		*(int *)win = color |
		((g->ray / 7) * 0x01000000 * (g->flags & crt_f));
	}
}

void		ft_paint_tex(t_game *g, t_ray pt, int offset, int i)
{
	char	*win;
	char	*tex;

	if (pt.y >= 0 && pt.y < (int)g->wnd->height)
	{
		tex = g->tex->addr + (int)(i * g->tex->line_l
			+ offset * (g->tex->bpp >> 3));
		if (*(int*)tex == 0x010101)
			return ;
		win = g->frm->addr + ((int)pt.y * g->frm->line_l +
			(int)pt.x * (g->frm->bpp >> 3));
		*(int *)win = (*(int*)tex |
		((g->ray / 7) * 0x01000000 * (g->flags & crt_f)));
	}
}
