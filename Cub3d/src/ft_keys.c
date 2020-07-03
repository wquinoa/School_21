/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:12:59 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 17:44:56 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void			ft_wasd(t_game *g, const int8_t dir, int8_t flag,
					t_trig wasd)
{
	int				i;
	const float		*x_pos = &g->plr->x;
	const float		*y_pos = &g->plr->y;

	i = -1 + flag;
	while (++i <= g->plr->speed &&
	g->map[((int)(*y_pos + dir * 8 * wasd.sin_v)) >> 6]
	[((int)(*x_pos + dir * 8 * wasd.cos_v)) >> 6] != '1')
	{
		g->plr->x += wasd.cos_v * dir;
		g->plr->y += wasd.sin_v * dir;
	}
}

static inline char	ft_direction(int key)
{
	const char	keys[8] = {s_key, dn, a_key, lf, w_key, up, d_key, rt};

	if (ft_memchr(keys, key, 4))
		return (-1);
	return (ft_memchr(&keys[4], key, 4) ? 1 : 0);
}

static void			key_press2(int key, t_game *g, char dir)
{
	if (key == rt || key == lf || key == d_key || key == a_key)
	{
		g->plr->dir += (ROTATION * dir);
		g->plr->dir -= (g->plr->dir > 2 * M_PI) * 2 * M_PI;
		g->plr->dir += (g->plr->dir < 0) * 2 * M_PI;
	}
	if (g->mcur != g->xcur && abs(g->xcur - g->mcur) > g->plr->dm)
	{
		if (g->mcur > g->xcur)
			g->plr->dir += g->plr->deltaray * abs(g->xcur - g->mcur) / 2;
		if (g->mcur < g->xcur)
			g->plr->dir -= g->plr->deltaray * abs(g->xcur - g->mcur) / 2;
		g->xcur += (g->mcur > g->xcur) ? (g->plr->dm) : -(g->plr->dm);
	}
}

int					key_press(int key, t_game *g)
{
	int			i;
	t_trig		wasd;
	const char	dir = ft_direction(key);

	mlx_clear_window(g->wnd->mlx, g->wnd->win);
	if (key == esc)
		exit(0);
	i = 0;
	ft_bzero(&wasd, sizeof(wasd));
	if (key == w_key || key == up || key == s_key || key == dn)
	{
		wasd.cos_v = cosf(g->plr->dir);
		wasd.sin_v = sinf(g->plr->dir);
		ft_wasd(g, dir, 0, wasd);
	}
	key_press2(key, g, dir);
	ft_draw_scene(g, g->frm, g->wnd);
	return (0);
}

int					ft_move_mouse(int x, int y, t_game *g)
{
	if (x < 0 || x > g->wnd->width)
	{
		g->xcur = g->x0;
		g->mcur = g->x0;
		mlx_mouse_move(g->wnd->win, g->x0, g->y0);
	}
	else
		g->mcur = x;
	y = 0;
	g->mcur != g->xcur ? key_press(-1, g) : 0;
	return (0);
}
