/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 14:22:20 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/03 14:28:52 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_o/t_map.h"

static void	ft_draw_wall(int x_pos, int y_pos, t_frame *f, size_t color)
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

static void	ft_draw_tile(int x_pos, int y_pos, t_frame *f, size_t color)
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