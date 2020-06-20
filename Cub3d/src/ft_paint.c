/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:15:59 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/20 18:04:33 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_blend(int fg, int bg, uint16_t amount)
{
	const int r = (((fg & red) >> 16) / 64 * amount) +
				(((bg & red) >> 16) / 64 * (64 - amount));
	const int g = (((fg & grn) >> 8) / 64 * amount) +
				(((bg & grn) >> 8) / 64 * (64 - amount));
	const int b = (((fg & blu) >> 0) / 64 * amount) +
				(((bg & blu) >> 0) / 64 * (64 - amount));
	return (((r << 16) & red) | ((g << 8) & grn) | (b & blu));
}

void	ft_paint(t_frame *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
	*(int *)dst = color;
}

void	ft_mix(t_frame *f, int x, int y, int color)
{
	char *dst;
	dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
	*(int*)dst = ft_blend(*(int*)dst, color, 32);
}

void	ft_blend_tex(t_game *g, int x, int y, int offset, int i)
{
	char	*win;
	char	*tex;
	int		color;

	if (y >= 0 && y < g->wnd->height)
	{
		tex = g->tex->addr + (int)((HEIGHT - i - 1) * g->tex->line_l +
			offset * (g->tex->bpp / 8));
		win = g->frm->addr + (y * g->frm->line_l + x * (g->frm->bpp / 8));
		color = ft_blend(g->txr->flr, *((int*)tex),
				(i < 56) ? (36 + i / 2) : 64);
		if (g->flags & crt_f)
			*(int *)win = color | ((g->ray / 8) * 0x01000000);
		else
			*(int *)win = color;
	}
}

void	ft_paint_tex(t_game *g, int x, int y, int offset, int i)
{
	char	*win;
	char	*tex;

	if (y >= 0 && y < g->wnd->height)
	{
		tex = g->tex->addr + (int)(i * g->tex->line_l + offset * (g->tex->bpp >> 3));
		win = g->frm->addr + (y * g->frm->line_l + x * (g->frm->bpp >> 3));
		if (g->flags & crt_f)
			*(int *)win = (*(int *)tex | ((g->ray / 8) * 0x01000000));
		else
			*(int *)win = *(int *)tex;
	}
}
