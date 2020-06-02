/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:35:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/03 02:37:27 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_o/mlx.h"
#include "../minilibx_o/t_map.h"
#include "../minilibx_o/get_next_line.h"
#include "../minilibx_o/libft.h"

#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	**ft_read_map(u_int16_t rows, t_game *g, char *av);

void	ft_init_player(char dir, int x_pos, int y_pos, t_game *g)
{
	g->plr->x = (x_pos) * g->frm->scale;
	g->plr->y = (y_pos) * g->frm->scale;

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

void	ft_paint(t_frame *f, int x, int y, int color)
{
	char *dst;

	dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
	*(uint16_t *)dst = color;
}

//static inline uint64_t	ft_sides(double k)
//{
	//if (k >= 3 * M_PI_2 && k < 2 * M_PI)
		//return (0x000000FE);
	//else if (k >= M_PI && k < 3 * M_PI_2)
		//return (0x0000FEFE);
	//else if (k >= M_PI_2 && k < M_PI)
		//return (0x00AAAAAA);
	//else
//}

void	ft_draw_rectangle(uint16_t ray, double k, t_game *g)
{
	const uint16_t	x0 = g->wnd->width / 2;
	uint16_t		x;
	uint16_t		y;
	uint8_t			i;
	const uint64_t	color = 0xEE;//ft_sides(fabs(k));

	y = ray + g->wnd->height / 4;
	while (y < g->wnd->height - (ray + g->wnd->height / 4))
	{
		x = x0 - k * (M_PI_4 / 0.001);
		i = 0;
		ft_paint(g->frm, x, y, (color - ray * 2 > 0x000EE) ? 0x09 : color - ray * 2);
		y++;
	}
}

void	ft_cast_ray(t_game *g)
{
	double x;
	double y;
	const double s = g->frm->scale;
	double k = g->plr->dir - M_PI / 4;
	uint16_t		i;

	while (k < (g->plr->dir + M_PI / 4))
	{
		i = 0;
		x = g->plr->x;
		y = g->plr->y;
		while (i < s && g->map[(int)(y / s)][(int)(x / s)] != '1')
		{
			ft_paint(g->frm, x, y, 0xFF00BB);
			x += cos(k);
			y += sin(k);
			i++;
		}
		while (g->map[(int)(y / s)][(int)(x / s)] != '1')
		{
			ft_paint(g->frm, x, y, 0xFF00BB);
			x += cos(g->plr->dir);
			y += sin(g->plr->dir);
			i++;
		}
		ft_draw_rectangle(i, g->plr->dir - k, g);
		k += (double)(0.001);
	}
}

void	ft_draw_player(t_game *g)
{
	uint16_t	x0;
	uint16_t	x;
	uint16_t	y;

	x = g->plr->x;
	x0 = x;
	y = g->plr->y;
	while (y <= g->plr->y + sqrt(g->frm->scale))
	{
		x = x0;
		while (x <= g->plr->x + sqrt(g->frm->scale))
			ft_paint(g->frm, x++, y, 0xFF7731);
		y++;
	}
	ft_cast_ray(g);
}

void	ft_draw_wall(int x_pos, int y_pos, t_frame *f, size_t color)
{
	int x = x_pos * f->scale;
	int y = y_pos * f->scale;
	const int x_lim = (x_pos + 1) * f->scale;
	const int y_lim = (y_pos + 1) * f->scale;

	while (y < y_lim)
	{
		x = x_pos * f->scale;
		while (x < x_lim)
			ft_paint(f, x++, y, color -= 216 / (int)sqrt(f->scale));
		y++;
	}
}

void	ft_draw_tile(int x_pos, int y_pos, t_frame *f, size_t color)
{
	int i = x_pos * f->scale;//f->scale;
	int j = y_pos * f->scale;//f->scale;
	const int x_lim = (x_pos + 1) * f->scale;
	const int y_lim = (y_pos + 1) * f->scale;

	while (j <= y_lim)
	{
		i = x_pos * f->scale;
		if (j % 2 == 1)
			while (i <= x_lim)
				ft_paint(f, i++, j, color);
		else
			while (i <= x_lim)
				ft_paint(f, i++, j, color * 2);
		color += 512 / (int)sqrt(f->scale);
		j++;
	}
}

void	ft_minimap(t_game *g, t_frame *f)
{
	int x_pos = 0;
	int y_pos= 0;
	char	*str;

	g->frm->scale = g->wnd->width / 120;
	while (g->map[y_pos])
	{
		str = g->map[y_pos];
		x_pos = 0;
		while (str[x_pos])
		{
			if (str[x_pos] == '1')
				ft_draw_wall(x_pos, y_pos, f, 0x007ff0);
			else if (str[x_pos] == '0')
				ft_draw_tile(x_pos, y_pos, f, 0x99cccc);
			else if (str[x_pos] == '2')
				ft_draw_wall(x_pos, y_pos, f, 0xffff00);
			else if (str[x_pos] == 'N')
			{
				ft_init_player(str[x_pos], x_pos, y_pos, g);
				str[x_pos] = '0';
				ft_draw_tile(x_pos, y_pos, f, 0x99cccc);
			}
			x_pos++;
		}
		y_pos++;
	}
}

void	ft_draw_map(t_game *g, t_frame * f, t_window *w)
{
	f->img = mlx_new_image(w->mlx, w->width, w->height);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_l, &f->en);
	ft_minimap(g, f);
	ft_draw_player(g);
	mlx_put_image_to_window(w->mlx, w->win, f->img, 0, 0);
	ft_debug_info(g);
	mlx_destroy_image(w->mlx, f->img);
}

int8_t	ft_direction(int key)
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
	//printf("%d, %d", g->wnd->width, g->wnd->height);
	if (key == esc)
		exit(0);
	if (key == w_key || key == up || key == s_key || key == dn)
	{
		while (i <= SPEED)
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
		window.width = 640;
		window.height = 480;
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
