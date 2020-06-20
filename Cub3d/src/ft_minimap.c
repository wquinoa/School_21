/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 14:22:20 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/20 17:17:13 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_draw_wall(int x_pos, int y_pos, t_game *g, int color)
{
	const uint16_t	mod = g->wnd->width / (HEIGHT * 2);
	const uint16_t	x_lim = (x_pos + 1) * mod;
	const uint16_t	y_lim = (y_pos + 1) * mod;
	uint16_t		i;
	uint16_t		j;

	j = y_pos * mod;
	while (j < y_lim)
	{
		i = x_pos * mod;
		while (i < x_lim)
		{
			ft_mix(g->frm, i, j, color);
			i++;
		}
		j++;
	}
}

//static void	ft_draw_tile(int x_pos, int y_pos, t_game *g, int color)
//{
	//const uint16_t	mod = g->wnd->width / (HEIGHT * 2);
	//const uint16_t	x_lim = (x_pos + 1) * mod;
	//const uint16_t	y_lim = (y_pos + 1) * mod;
	//uint16_t		i;
	//uint16_t		j;

	//j = y_pos * mod;
	//while (j <= y_lim)
	//{
		//i = x_pos * mod;
		//if (j % (HEIGHT / 4) == 1)
			//while (i <= x_lim)
				//ft_mix(g->frm, i++, j, color + 64);
		//else
			//while (i <= x_lim)
				//ft_mix(g->frm, i++, j, color);
		//j++;
	//}
//}

void	ft_minimap(t_game *g)
{
	int x_pos = 0;
	int y_pos = 0;
	char	*str;

	while (g->map[y_pos])
	{
		str = g->map[y_pos];
		x_pos = 0;
		while (str[x_pos])
		{
			if (str[x_pos] == '1' && g->flags & 4)
				ft_draw_wall(x_pos, y_pos, g, 0xFFFFFF);
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