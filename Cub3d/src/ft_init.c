/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:35:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/05 00:39:42 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_o/mlx.h"
#include "../minilibx_o/t_map.h"
#include "../minilibx_o/get_next_line.h"
#include "../minilibx_o/libft.h"

#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_read_map(u_int16_t rows, t_game *g, char *av);

void	ft_init_player(char dir, int x_pos, int y_pos, t_game *g)
{
	g->plr->x = (x_pos) * g->frm->scale;
	g->plr->y = (y_pos) * g->frm->scale;
	if (!(g->wnd->width % 4) && !(g->wnd->height % 3))
		g->plr->fov = 66 * M_PI / 180;
	else
		g->plr->fov = 66 * M_PI / 180;
	g->plr->speed = sqrt(g->frm->scale);

	if (dir == 'N')
		g->plr->dir = 3 * M_PI_2;
	else if (dir == 'W')
		g->plr->dir = 0;
	else if (dir == 'S')
		g->plr->dir = M_PI_2;
	else if (dir == 'E')
		g->plr->dir = M_PI;
}

void	ft_debug_info(t_game *g)
{
	double k = g->plr->dir;
	char *direction = ft_strjoin_dlm(ft_itoa((int)k), "." , ft_itoa(fabs(k - (int)k) * 100));

	mlx_string_put(g->wnd->mlx, g->wnd->win, 10, 20, 0xFFDDDD, "Direction:");
	mlx_string_put(g->wnd->mlx, g->wnd->win, 90, 20, 0xFFDDDD, direction);
	free(direction);
}

void	ft_paint(t_frame *f, int x, int y, uint32_t color)
{
	char *dst;

	dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
	*(uint32_t *)dst = color;
}

void	ft_floor(t_game *g)
{
	int x;
	int y;
	uint64_t floor = 0x777773;
	uint64_t ceil = 0x77777a;

	y = 0;
	while (y < g->wnd->height / 2)
	{
		x = 1;
		while (x < g->wnd->width)
			ft_paint(g->frm, x++, y, ceil + y / 4);
		y++;
	}
	while (y < g->wnd->height)
	{
		x = 1;
		while (x < g->wnd->width)
			ft_paint(g->frm, x++, y, 0x333333);
		y++;
	}
}

void	ft_draw_vline(uint16_t ray, double k, t_game *g)
{
	const double	x0 = g->wnd->width / 2;
	const double	y0 = g->wnd->height / 2;
	uint16_t		x;
	uint16_t		y;
	const uint64_t	color = 0x0000ff;

//	y = ray + g->wnd->height / HEIGHT;
	//while (y < g->wnd->height - (ray + g->wnd->height / HEIGHT))
	//{
		//x = x0 - k * g->wnd->width / g->plr->fov;
		//ft_paint(g->frm, x, y, (color - ray * 2 > 0x000EE) ? 0x09 : color - ray * 2);
		//y++;
	//}
	double delta = g->frm->scale / 2 * g->wnd->height / (ray * cos(k));
	if (delta > g->wnd->height / 2)
		delta = g->wnd->height / 2;
	y = y0 - delta;
	while (y < y0 + delta)
	{
		x = x0 - k * g->wnd->width / g->plr->fov;
		ft_paint(g->frm, x, y, (color - (ray / g->plr->speed)));
		y++;
	}
}

void	ft_cast_ray(t_game *g, t_player *plr, t_frame *frm)
{
	double x;
	double y;
	const double	s = frm->scale;
	double			k = plr->dir - plr->fov / 2;
	uint16_t		i;

	while (k < (plr->dir + plr->fov / 2))
	{
		i = 0;
		x = plr->x;
		y = plr->y;
		while (g->map[(int)(y / s)][(int)(x / s)] != '1')// && i < s * 2)
		{
			ft_paint(frm, x / 4, y / 4, 0x00DD00DD);
			x += cos(k);
			y += sin(k);
			i++;
		}
//		i = 0;
//		while (g->map[(int)(y / s)][(int)(x / s)] != '1')
		//{
			//ft_paint(frm, x / 4, y / 4, 0x550055);
			//x += cos(plr->dir);
			//y += sin(plr->dir);
			//i++;
		//}
		ft_draw_vline(i, plr->dir - k, g);
		k += (double)(plr->fov / (g->wnd->width * 1.2));
	}
}

void	ft_draw_player(t_game *g)
{
	uint16_t	x0;
	uint16_t	x;
	uint16_t	y;

	x = g->plr->x;
	x0 = x - 1;
	y = g->plr->y;
	while (y <= g->plr->y + sqrt(g->frm->scale))
	{
		x = x0;
		while (x <= g->plr->x + sqrt(g->frm->scale))
			ft_paint(g->frm, x++ / 4, y / 4, 0xFF7731);
		y++;
	}
}

void	ft_draw_map(t_game *g, t_frame *f, t_window *w)
{
	f->img = mlx_new_image(w->mlx, w->width, w->height);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_l, &f->en);
	ft_floor(g);
	ft_minimap(g, f);
	ft_cast_ray(g, g->plr, g->frm);
	ft_draw_player(g);
	mlx_put_image_to_window(w->mlx, w->win, f->img, 0, 0);
	ft_debug_info(g);
	mlx_destroy_image(w->mlx, f->img);
}

static inline int8_t	ft_direction(int key)
{
	const uint8_t keys[8] = {w_key, up, a_key, rt, s_key, dn, d_key, lf};

	if (ft_memchr(&keys[4], key, 4))
		return (-1);
	else
		return (1);
}

int		key_press(int key, t_game *g)
{
	int i = 0;
	const int dir = ft_direction(key);
	const double vec = g->plr->dir;
	double *x_pos = &g->plr->x;
	double *y_pos = &g->plr->y;

	mlx_clear_window(g->wnd->mlx, g->wnd->win);
	if (key == esc)
		exit(0);
	if (key == w_key || key == up || key == s_key || key == dn)
	{
		while (i <= g->plr->speed)
		{
			if(g->map[((int)(*y_pos + dir * sin(vec)))/ g->frm->scale]\
			[((int)(*x_pos + dir * cos(vec))) / g->frm->scale] != '1')
			{
				g->plr->x += cos(vec) * dir;
				g->plr->y += sin(vec) * dir;
			}
			i++;
		}
	}
	else if (key == rt || key == lf)
	{
		g->plr->dir += (ROTATION * dir);
		g->plr->dir -= (g->plr->dir > 2 * M_PI) * 2 * M_PI;
		g->plr->dir += (g->plr->dir < 2 * -M_PI) * 2 * M_PI;
	}
	ft_draw_map(g, g->frm, g->wnd);
	return (0);
}

void	ft_init(char *av)
{
	t_game				scene;
	static t_window		window;
	static t_texture	texture;
	static t_player		player;
	static t_frame		f;

	scene.wnd = &window;
	scene.txr = &texture;
	scene.plr = &player;
	scene.frm = &f;
	scene.map = ft_read_map(0, &scene, av);
	window.mlx =  mlx_init();
	if (window.width < 320 || window.height < 240)
	{
		window.width = 320;
		window.height = 240;
	}
	window.win = mlx_new_window(window.mlx, window.width, window.height, "Placeholder name");
	ft_draw_map(&scene, &f, &window);
	mlx_hook(window.win, 2, 0, &key_press, &scene);
	mlx_loop(window.mlx);
}

int main(int argc, char **argv)
{
	if (argc)
		ft_init(argv[1]);
}
