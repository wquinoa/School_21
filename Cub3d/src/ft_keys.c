/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:12:59 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/20 20:01:48 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static inline char	ft_direction(int key)
{
	const char keys[8] = {s_key, dn, d_key, lf};

	if (ft_memchr(keys, key, 4))
		return (-1);
	else
		return (1);
}


static void	ft_wasd(t_game *g, const int8_t dir, int8_t flag, t_trig wasd)
{
	int			i;
	float		*x_pos = &g->plr->x;
	float		*y_pos = &g->plr->y;

	i = -1;
	if (flag == 0)
		while (++i <= g->plr->speed &&
		g->map[((int)(*y_pos + dir * 8 * wasd.sin_v)) / HEIGHT]
		[((int)(*x_pos + dir * 8 * wasd.cos_v)) / HEIGHT] != '1')
		{
			g->plr->x += wasd.cos_v * dir;
			g->plr->y += wasd.sin_v * dir;
		}
	else
		while (++i < g->plr->speed &&
		g->map[((int)(*y_pos + 8 * wasd.sin_v_pi_2)) / HEIGHT]
		[((int)(*x_pos + 8 * wasd.cos_v_pi_2)) / HEIGHT] != '1')
		{
			g->plr->x += wasd.cos_v_pi_2;
			g->plr->y += wasd.sin_v_pi_2;
		}
}

static void	key_press2(int key, t_game *g, char dir)
{
	if (key == rt || key == lf || key == d_key || key == a_key)
	{
		g->plr->dir += (ROTATION * dir);
		g->plr->dir -= (g->plr->dir > 2 * M_PI) * 2 * M_PI;
		g->plr->dir += (g->plr->dir < 0) * 2 * M_PI;
	}
	if (key == c_key)
		g->flags ^= crt_f;
	else if (key == h_key)
	{
		g->flags ^= hal_f;
		g->flags |= crt_f;
	}
	else if (key == m_key)
		g->flags ^= map_f;
	else if (key == t_key)
		g->flags ^= tex_f;
	else if (key == pl_key && g->plr->speed < 48)
		g->plr->speed += 4;
	else if (key == mi_key && g->plr->speed > 12)
		g->plr->speed -= 4;
	else if (key == r_key)
		g->flags ^= ref_f;
}

int		key_press(int key, t_game *g)
{
	int			i;
	t_trig		wasd;
	const char	dir = ft_direction(key);

	i = 0;
	ft_bzero(&wasd, sizeof(wasd));
	mlx_clear_window(g->wnd->mlx, g->wnd->win);
	if (key == esc)
		exit(0);
	if (key == w_key || key == up || key == s_key || key == dn)
	{
		wasd.cos_v = cos(g->plr->dir);
		wasd.sin_v = sin(g->plr->dir);
		ft_wasd(g, dir, 0, wasd);
	}
	else if (key == a_key || key == d_key)
	{
		wasd.cos_v_pi_2 = cos(g->plr->dir - dir * M_PI_2);
		wasd.sin_v_pi_2 = sin(g->plr->dir - dir * M_PI_2);
		ft_wasd(g, dir, 1, wasd);
	}
	else
		key_press2(key, g, dir);
	ft_draw_scene(g, g->frm, g->wnd);
	return (0);
}