/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapval.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:40:33 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 04:42:43 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int8_t	ft_strval2(const char *id, char *str, t_game *g)
{
	if (id[0] == 'C' || id[0] == 'F')
		ft_get_color(id[0], str, g);
	else if (ft_strchr("NSWE", id[0]))
		ft_get_link(id, str, g);
	else if (id[0] == 'R' && !(g->flags & res_f))
	{
		ft_check_res(g->wnd, str);
		g->x0 = g->wnd->width >> 1;
		g->y0 = g->wnd->height >> 1;
	}
	else
		ft_errors(dup_res);
	if (g->wnd->height < 0 || g->wnd->width < 0)
		ft_errors(bad_sym);
	return (id[0]);
}

int8_t			ft_strval(char *str, t_game *g)
{
	const char	*id[9] = {"NO", "SO", "WE", "EA", "S ", "F ", "C ", "R ", NULL};
	short		i;

	i = -1;
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (0);
	while (id[++i])
		if ((ft_strncmp(str, id[i], 2)) == 0)
			return (ft_strval2(id[i], str, g));
	while (*str)
		if (!(ft_strchr("012 NEWS", *str++)))
			ft_errors(bad_sym);
	return (1);
}

static void		flood_fill(char **region, uint16_t x, uint16_t y)
{
	if (region[y][x] == '1' || region[y][x] == '.')
		return ;
	if (region[y][x] == ' ')
	{
		write(1, "Map not enclosed.\n", 18);
		exit(0);
	}
	region[y][x] = '.';
	flood_fill(region, x + 1, y);
	flood_fill(region, x - 1, y);
	flood_fill(region, x, y + 1);
	flood_fill(region, x, y - 1);
	flood_fill(region, x - 1, y - 1);
	flood_fill(region, x + 1, y + 1);
	flood_fill(region, x - 1, y + 1);
	flood_fill(region, x + 1, y - 1);
}

static void		ft_find_plr(char **test, t_ray *pos, t_game *g)
{
	short i;
	short j;

	i = -1;
	while (test[++i])
	{
		j = -1;
		while (test[i][++j])
		{
			if (ft_strchr("NEWS", test[i][j]))
			{
				(g->flags & pla_f) ? ft_errors(bad_map) : 0;
				g->flags |= pla_f;
				pos->x = j;
				pos->y = i;
			}
		}
	}
	!(g->flags & pla_f) ? ft_errors(bad_map) : 0;
}

void			ft_mapval(char **map, uint16_t rows, t_game *g)
{
	char	**test;
	short	i;
	t_ray	pos;

	if (!(test = (char **)malloc(sizeof(char *) * (rows + 1))))
		ft_errors(bad_malloc);
	i = -1;
	while (map[++i])
		!(test[i] = ft_strdup(map[i])) ? ft_errors(bad_malloc) : 0;
	test[i] = NULL;
	ft_bzero(&pos, sizeof(t_ray));
	ft_find_plr(test, &pos, g);
	flood_fill(test, pos.x, pos.y);
	i = -1;
	while (test[++i])
		free(test[i]);
	free(test);
}
