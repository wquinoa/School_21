/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 20:00:30 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/20 18:06:20 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_get_link(const char *c, char *str, t_game *g)
{
	char		*link;
	uint16_t	i;

	i = 0;
	link = str + 2;
	while (*link && ft_isspace(*link))
		link++;
	while (link[i] && !(ft_isspace(link[i])))
		i++;
	link[i] = '\0';
	if (*c == 'N')
		g->txr->no = ft_strdup(link);
	else if (*c == 'S' && *(c + 1) == 'O')
		g->txr->so = ft_strdup(link);
	else if (*c == 'S' && *(c + 1) == ' ')
		g->txr->sp = ft_strdup(link);
	else if (*c == 'E')
		g->txr->ea = ft_strdup(link);
	else if (*c == 'W')
		g->txr->we = ft_strdup(link);
	return (1);
}

static int8_t	ft_get_color(char c, char *str, t_game *g)
{
	int			tmp;
	int			a;
	uint8_t		i;

	i = 0;
	a = 0;
	while (i < 3)
	{
		str++;
		tmp = ft_atoi(str);
		if (tmp < 0 || tmp > 255)
			exit(0);
		a |= tmp << (2 - i) * 8;
		while (*str != ',' && *str)
			str++;
		i++;
	}
	if (c == 'F')
		g->txr->flr = a;
	else
		g->txr->ceil = a;
	return (1);
}

static int8_t	ft_strval2(const char *id, char *str, t_game *g)
{
	if (id[0] == 'C' || id[0] == 'F')
		ft_get_color(id[0], str, g);
	else if (ft_strchr("NSWE", id[0]))
		ft_get_link(id, str, g);
	else if (id[0] == 'R')
	{
		g->wnd->width = ft_atoi(str + 1);
		while (ft_isspace(*str))
			str++;
		str += ft_nlen(g->wnd->width);
		g->wnd->height = ft_atoi(str + 2);
		while (ft_isspace(*str))
			str++;
		str += ft_nlen(g->wnd->width);
		g->x0 = g->wnd->width / 2;
		g->y0 = g->wnd->height / 2;
	}
	return (id[0]);
}

static int8_t	ft_strval(char *str, t_game *g)
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
			return (-1);
	return (1);
}

void	flood_fill(char **region, uint16_t x, uint16_t y)
{
	if (region[y][x] == '1' || region[y][x] == '.')
		return ;
	if (region[y][x] == ' ')
	{
		write(1, "lol\n", 4);
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

void	ft_mapval(char **map, uint16_t rows)
{
	char	**test;
	short	i;
	short	j;

	if (!(test = (char **)malloc(sizeof(char *) * (rows + 1))))
		return ;
	i = -1;
	while (map[++i])
		test[i] = ft_strdup(map[i]);
	i = -1;
	while (test[++i])
	{
		j = -1;
		while (test[i][++j])
		{
			if (ft_strchr("NEWS", test[i][j]))
				flood_fill(test, j, i);
		}
	}
}

char	**ft_lsttab(t_list *list, u_int16_t rows, uint16_t columns)
{
	char	**map;
	short	i;

	if (!(map = (char **)malloc(sizeof(char *) * ((rows += 2) + 1))))
		return (NULL);
	i = -1;
	columns += 2;
	while (++i < rows)
	{
		map[i] = ft_calloc(1, columns + 1);
		ft_memset(map[i], ' ', columns);
		if (i > 0 && list)
		{
			ft_strlcpy(map[i] + 1, list->content, columns - 1);
			list = list->next;
		}
	}
	map[i] = NULL;
	ft_lstclear(&list, &free);
	ft_mapval(map, rows);
	return (map);
}

char	**ft_read_map(uint16_t rows, uint16_t longest, t_game *g, char *av)
{
	const int		fd = open(av, O_RDONLY);
	t_list			*list;
	t_list			*tmp;
	char			*str;
	int				flag;

	tmp = NULL;
	list = NULL;
	while ((flag = get_next_line(fd, &str)) >= 0)
	{
		if (!(tmp = ft_lstnew(ft_strdup(str))))
			flag = -1;
		if (ft_strval(str, g) == 1)
		{
			rows++;
			longest = longest > ft_strlen(str) ? longest : ft_strlen(str);
			ft_lstadd_back(&list, tmp);
		}
		free(str);
		if (flag == 0)
			break ;
	}
	close(fd);
	return (ft_lsttab(list, rows, longest));
}
