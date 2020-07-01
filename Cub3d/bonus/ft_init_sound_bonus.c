/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sound_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:48:12 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 16:03:07 by wquinoa          ###   ########.fr       */
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
