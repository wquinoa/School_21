/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sound_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:48:12 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 15:31:23 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_init_sound(t_game *g, t_frame *es)
{
	es->img = mlx_xpm_file_to_image(g->wnd->mlx, "./textures/yd.xpm",
	&es->width, &es->height);
	es->addr = mlx_get_data_addr(es->img, &es->bpp, &es->line_l, &es->en);
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
	playMusic("music/Neydah_-_Inversions.wav", SDL_MIX_MAXVOLUME / 6);
}

void	ft_countdown(void)
{
	char	buf[14];
	int		i;

	i = 0;
	ft_putstr_fd("\033[66;1mIn 5...\033[0;1m", 1);
	ft_memcpy(buf, "\033[35;1m    ...", 14);
	buf[3] = 6;
	write(1, "\033[35;1m", 7);
	usleep(900000);
	while (i++ < 4)
	{
		usleep(700000);
		buf[10] = 5 - i + '0';
		(i == 3) ? write(1, "\033[36;1m", 7) : 0;
		write(1, buf, 14);
	}
	usleep(1250000);
	ft_putendl_fd("\033[36m!", 1);
}
