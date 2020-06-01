/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:35:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/02 01:36:18 by wquinoa          ###   ########.fr       */
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

char	**ft_read_map(u_int16_t rows, t_game *g);

void	ft_init_player(char dir, int x_pos, int y_pos, t_player *plr)
{
	plr->x = (x_pos) * SCALE;
	plr->y = (y_pos) * SCALE;

	if (dir == 'N')
		plr->dir = 3 * M_PI_2;
	else if (dir == 'W')
		plr->dir = 0;
	else if (dir == 'S')
		plr->dir = M_PI_2;
	else if (dir == 'E')
		plr->dir = M_PI;


}

void	ft_debug_info(t_game *g)
{
	double k = g->plr->dir;
	char *direction = ft_strjoin_dlm(ft_itoa((int)k), "." , ft_itoa(fabs(k - (int)k) * 100));

	mlx_string_put(g->wnd->mlx, g->wnd->win, 10, 20, 0xFFDDDD, "Direction:");
	mlx_string_put(g->wnd->mlx, g->wnd->win, 90, 20, 0xFFDDDD, direction);
	free(direction);
}

void	ft_draw_rectangle(uint16_t ray, double k, t_game *g)
{
	uint16_t x0 = g->wnd->width / 2;
	uint16_t y0 = g->wnd->height / 2;
	uint16_t x;
	uint16_t y;
	uint8_t	i = 0;
	uint32_t color = 0x0AA00;

	y = ray * SCALE;
	while (y < g->wnd->height - ray * SCALE)
	{
		x = x0 + k * 2 * SQ(SCALE);
		i = 0;
		while (i++ < SCALE)
		{
			mlx_pixel_put(g->wnd->mlx, g->wnd->win, x, y, color - fabs(x / sqrt(SCALE / 2)));
			x++;
		}
		y++;
	}
}

void	ft_cast_ray(t_game *g)
{
	double x = g->plr->x;
	double y = g->plr->y;
	double k = g->plr->dir - M_PI_4;
	uint16_t		i = 0;

	ft_debug_info(g);
	while (k < (g->plr->dir + M_PI_4))
	{
		i = 0;
		while (i++ <= SCALE * 4)
		{
			if (g->map[COL(y)][COL(x)] == '1')
			{
				ft_draw_rectangle(i, g->plr->dir - k, g);
				break ;
			}
			mlx_pixel_put(g->wnd->mlx, g->wnd->win, x, y, 0xFF00BB);
			x += cos(k);
			y += sin(k);
		}
		x = g->plr->x;
		y = g->plr->y;
		k += (double)(0.03);
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
	while (y <= g->plr->y + sqrt(SCALE))
	{
		x = x0;
		while (x <= g->plr->x + sqrt(SCALE))
			mlx_pixel_put(g->wnd->mlx, g->wnd->win, x++, y, 0xFF7731);
		y++;
	}
	ft_cast_ray(g);
}

void	ft_draw_wall(int x_pos, int y_pos, t_window *w, size_t color)
{
	int i = x_pos * SCALE;
	int j = y_pos * SCALE;
	const int x_lim = (x_pos + 1) * SCALE;
	const int y_lim = (y_pos + 1) * SCALE;

	while (j < y_lim)
	{
		i = x_pos * SCALE;
		while (i < x_lim)
			mlx_pixel_put(w->mlx, w->win, i++, j, color-= 216 / (int)sqrt(SCALE));
		j++;
	}
}

void	ft_draw_tile(int x_pos, int y_pos, t_window *w, size_t color)
{
	int i = x_pos * SCALE;
	int j = y_pos * SCALE;
	const int x_lim = (x_pos + 1) * SCALE;
	const int y_lim = (y_pos + 1) * SCALE;

	while (j <= y_lim)
	{
		i = x_pos * SCALE;
		if (j % 2 == 1)
			while (i <= x_lim)
				mlx_pixel_put(w->mlx, w->win, i++, j, color);
		else
			while (i <= x_lim)
				mlx_pixel_put(w->mlx, w->win, i++, j, color * 2);
		color += 512 / (int)sqrt(SCALE);
		j++;
	}
}

void	ft_draw_map(t_game *g)
{
	int x_pos = 0;
	int y_pos= 0;
	char	*str;


	while (g->map[y_pos])
	{
		str = g->map[y_pos];
		x_pos = 0;
		while (str[x_pos])
		{
			if (str[x_pos] == '1')
				ft_draw_wall(x_pos, y_pos, g->wnd, 0x007ff0);
			else if (str[x_pos] == '0')
				ft_draw_tile(x_pos, y_pos, g->wnd, 0x99cccc);
			else if (str[x_pos] == '2')
				ft_draw_wall(x_pos, y_pos, g->wnd, 0xffff00);
			else if (str[x_pos] == 'N')
			{
				ft_init_player(str[x_pos], x_pos, y_pos, g->plr);
				str[x_pos] = '0';
				ft_draw_tile(x_pos, y_pos, g->wnd, 0x99cccc);
			}
			x_pos++;
		}
		y_pos++;
	}
	ft_draw_player(g);
	//ft_draw_wall(g->plyr->x + offset, g->plyr->y + y_offset, SCALE, g->wndw, 0x00f0f0);
}

int		key_press(int key, t_game *g)
{

	printf("key: %d\n", key);
	mlx_clear_window(g->wnd->mlx, g->wnd->win);
	if (key == esc)
		exit(0);
	if (key == w_key || key == up)
	{
		g->plr->y -= 3;
		while (g->map[g->plr->y/SCALE][g->plr->x/SCALE] == '1')
			g->plr->y += 1;
	}
	else if (key == a_key)
	{
		g->plr->x -= 3;
		while (g->map[g->plr->y/SCALE][g->plr->x/SCALE] == '1')
			g->plr->x += 1;
	}
	if (key == s_key || key == dn)
	{
		g->plr->y += 3;
		while (g->map[g->plr->y/SCALE][g->plr->x/SCALE] == '1')
			g->plr->y -= 1;
	}
	else if (key == d_key)
	{
		g->plr->x += 3;
		while (g->map[g->plr->y/SCALE][g->plr->x/SCALE] == '1')
			g->plr->x -= 1;
	}
	else if (key == lf)
		g->plr->dir -= ROTATION;
	else if (key == rt)
		g->plr->dir += ROTATION;
	ft_draw_map(g);
	return (0);
}

void	ft_init(void)
{
	t_game				scene;
	static t_window		window;
	static t_texture	texture;
	static t_player		player;

	scene.wnd = &window;
	scene.txr = &texture;
	scene.plr = &player;
	scene.map = ft_read_map(0, &scene);
	window.mlx =  mlx_init();
	if (window.width < 640 || window.height < 480)
	{
		window.width = 640;
		window.height = 480;
	}
	window.win = mlx_new_window(window.mlx, window.width, window.height, "Placeholder name");
	ft_draw_map(&scene);
	mlx_hook(window.win, 2, 0, &key_press, &scene);
	mlx_loop(window.mlx);
}

int main(void)
{
	ft_init();
}
