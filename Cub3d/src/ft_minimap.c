/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 14:22:20 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 16:03:26 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_init_player(char dir, int x_pos, int y_pos, t_game *g)
{
	g->plr->x = (x_pos) * HEIGHT + (HEIGHT >> 1);
	g->plr->y = (y_pos) * HEIGHT + (HEIGHT >> 1);
	if (!(g->wnd->width % 16) && !(g->wnd->height % 9))
		g->plr->fov = 84 * M_PI / 180;
	else
		g->plr->fov = 66 * M_PI / 180;
	g->xcur = g->x0;
	g->mcur = g->x0;
	mlx_mouse_move(g->wnd->win, g->x0, g->y0);
	mlx_mouse_hide();
	g->plr->fov_2 = g->plr->fov / 2;
	g->plr->speed = sqrt(HEIGHT) * 2;
	g->plr->deltaray = (float)(g->plr->fov / (g->wnd->width * 1.1));
	g->plr->dm = g->wnd->width >> 4;
	if (dir == 'N')
		g->plr->dir = 3 * M_PI_2;
	else if (dir == 'E')
		g->plr->dir = 0;
	else if (dir == 'S')
		g->plr->dir = M_PI_2;
	else if (dir == 'W')
		g->plr->dir = M_PI;
}

void		ft_minimap(t_game *g)
{
	int		x_pos;
	int		y_pos;
	char	*str;

	y_pos = 0;
	while (g->map[y_pos])
	{
		str = g->map[y_pos];
		x_pos = 0;
		while (str[x_pos])
		{
			if (ft_strchr("NEWS", str[x_pos]))
			{
				ft_init_player(str[x_pos], x_pos, y_pos, g);
				str[x_pos] = '0';
			}
			x_pos++;
		}
		y_pos++;
	}
}
