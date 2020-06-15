/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 08:29:01 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/09 15:25:15 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdint.h>
#include "../minilibx_o/mlx.h"
#include "../minilibx_o/t_map.h"
#include "../minilibx_o/get_next_line.h"
#include "../minilibx_o/libft.h"

#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int *splitColors(int n)
{
	int *a;

	a = (int *)ft_calloc(3, sizeof(int));
	a[0] |= ((n & red) >> 16);
	a[1] |= ((n & grn) >> 8);
	a[2] |= ((n & blu));
	return (a);
}

int set_color(int r, int g, int b)
{
	return ((r << 16 | g << 8 | b));
}

int blendColorValue(int fg, int bg, int t)
{
	int *a1;
	int *b1;
	int r;
	int g;
	int b;

	a1 = splitColors(fg);
	b1 = splitColors(bg);
	r = ((100 - t) * a1[0] + t * b1[0]) / 100;
	g = ((100 - t) * a1[1] + t * b1[1]) / 100;
	b = ((100 - t) * a1[2] + t * b1[2]) / 100;
	free(a1);
	free(b1);
	return (set_color(r, g, b));
}

int main()
{
	t_game				scene;
	static t_window		window;
	static t_texture	texture;
	static t_player		player;
	static t_frame		f;
	int i = 0;
	int j = 0;
	int a;
	int b;
	int n;

	scene.wnd = &window;
	scene.txr = &texture;
	scene.plr = &player;
	scene.frm = &f;
	window.mlx =  mlx_init();
	window.width = 640;
	window.height = 480;
	window.win = mlx_new_window(window.mlx, window.width, window.height, "Placeholder name");
	player.x = window.width / 2;
	player.y = window.height / 2;
	a = set_color(255, 0, 0);
	b = set_color(0, 0, 255);
	n = blendColorValue(a, b, 70);
	while (j++ <= 50)
	{
		i = 0;
		while (i++ <= 50)
		{
			mlx_pixel_put(window.mlx, window.win, player.x + i, player.y + j, n);

		}
	}

	mlx_loop(window.mlx);
}