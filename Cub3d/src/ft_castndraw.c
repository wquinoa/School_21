/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_castndraw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:50:21 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/25 15:09:29 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_add_texture(uint16_t ray, float k, t_game *g, int tex_x)
{
	int				i;
	const float		halfwall = HEIGHT / 2 * g->wnd->height / (ray * cos(k));
	t_ray			point;

	i = 0;
	point.x = (g->x0 - k * g->wnd->width / g->plr->fov);
	point.y = g->y0 - halfwall - 1;
	g->depth[(int)point.x] = ray;
	ft_draw_ceil(g, point.x, point.y);
	while (++point.y < g->y0 + halfwall)
		ft_paint_tex(g, point, tex_x, i++ / ((halfwall * 2) / HEIGHT));
	if (g->flags & crt_f)
	{
		i = 0;
		while (++point.y < g->y0 + 3 * halfwall)
			ft_blend_tex(g, point, tex_x, i++ / ((halfwall * 2) / HEIGHT));
	}
	ft_draw_floor(g, point.x, point.y - 1);
}

static void	ft_drawing_handler(float k, t_game *g, t_ray ray)
{
	g->ray = ray.len;
	if ((int)(ray.x - cos(k)) / HEIGHT == (int)(ray.x / HEIGHT))
	{
		if ((int)(ray.y - sin(k)) / HEIGHT < (int)(ray.y / HEIGHT))
			g->tex = g->so;
		else if ((int)(ray.y - sin(k)) / HEIGHT > (int)(ray.y / HEIGHT))
			g->tex = g->no;
	}
	else if ((int)(ray.y - sin(k)) / HEIGHT == (int)(ray.y / HEIGHT))
	{
		if ((int)(ray.x - cos(k)) / HEIGHT < (int)(ray.x / HEIGHT))
			g->tex = g->ea;
		else if ((int)(ray.x - cos(k)) / HEIGHT > (int)(ray.x / HEIGHT))
			g->tex = g->we;
	}
	if ((int)(ray.x - cos(k)) / HEIGHT == (int)(ray.x / HEIGHT))
		ft_add_texture(ray.len, g->plr->dir - k, g, (int)ray.x % HEIGHT);
	else
		ft_add_texture(ray.len, g->plr->dir - k, g, (int)ray.y % HEIGHT);
}

void		ft_cast_ray(t_game *g, t_player *plr)
{
	float			k;
	t_ray			ray;

	k = plr->dir - plr->fov_2;
	while (k < (plr->dir + plr->fov_2))
	{
		ray.x = plr->x;
		ray.y = plr->y;
		ray.len = 0;
		while (g->map[(int)(ray.y / HEIGHT)][(int)(ray.x / HEIGHT)] != '1')
		{
			ray.x += cos(k);
			ray.y += sin(k);
			ray.len++;
		}
		ft_drawing_handler(k, g, ray);
		k += plr->deltaray;
	}
}
