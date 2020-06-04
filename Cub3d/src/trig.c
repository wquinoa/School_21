/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 20:15:37 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/03 20:57:56 by wquinoa          ###   ########.fr       */
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


int main(void)
{
	t_game				scene;
	static t_window		window;
	static t_texture	texture;
	static t_player		player;
	static t_frame		f;
	int i = 0;
	int j = 0;

	scene.wnd = &window;
	scene.txr = &texture;
	scene.plr = &player;
	scene.frm = &f;
	window.mlx =  mlx_init();
	window.width = 640;
	window.height = 480;
	window.win = mlx_new_window(window.mlx, window.width, window.height, "Placeholder name");
	player.dir = M_PI;
	player.x = window.width / 2;
	player.y = window.height / 2;
	while (j++ <= 50)
	{
		i = 0;
		while (i++ <= 50)
		{
			mlx_pixel_put(window.mlx, window.win, player.x + i * sin(player.dir), player.y + i * cos(player.dir), 0xAAAAAA);
		}
		player.x += sin(player.dir - M_PI_2);//-- sin(player.dir - M_PI_2);
		player.y += cos(player.dir - M_PI_2);// - cos(player.dir - M_PI_2);
	}

	mlx_loop(window.mlx);
}