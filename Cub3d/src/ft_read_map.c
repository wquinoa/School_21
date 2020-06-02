/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 20:00:30 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/03 01:52:04 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../minilibx_o/mlx.h"
#include "../minilibx_o/t_map.h"
#include "../minilibx_o/get_next_line.h"
#include "../minilibx_o/libft.h"

int		ft_get_link(const char *c, char *str, t_game *g)
{
	char		*link;
	uint16_t	i;

	i = 0;
	link = str + 2;
	while (ft_isspace(*link))
		link++;
	while (!(ft_isspace(link[i])))
		i++;
	link[i] = '\0';
	if (*c == 'N')
		g->txr->no = link;
	else if (*c == 'S' && *(c + 1) == 'O')
		g->txr->so = link;
	else if (*c == 'S' && *(c + 1) == ' ')
		g->txr->sp = link;
	else if (*c == 'E')
		g->txr->ea = link;
	else if (*c == 'W')
		g->txr->we = link;
	return (1);
}

static int8_t	ft_get_color(char c, char *str, t_game *g)
{
	int16_t	*a;
	uint8_t	i;

	if (!(a = (int16_t *)malloc(sizeof(int16_t) * 3)))
		return (0);
	i = 0;
	while (i < 3)
	{
		a[i] = ft_atoi(str + 1);
		if (a[i] < 0 || a[i] > 255)
		{
			ft_bzero(a, 3);
			return(0);
		}
		str = ft_strchr(str, ',');
	}
	if (c == 'F')
		g->txr->flr = a;
	else
		g->txr->ceil = a;
	return (1);
}

static int8_t	ft_strval(char *str, t_game *g)
{
	const char		*id[9] = {"NO", "SO", "WE", "EA", "S ", "F ", "C ", "R ", NULL};
	int8_t		i;

	i = -1;
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (0);
	while (id[++i])
		if ((ft_strncmp(str, id[i], 2)) == 0)
		{
			if (id[i][0] == 'C' || id[i][0] == 'F')
				ft_get_color(id[i][0], str, g);
			else if (ft_strchr("NSWE", id[i][0]))
				ft_get_link(id[i], str, g);
			else if (id[i][0] == 'R')
			{
				g->wnd->width = ft_atoi(str + 2);
				str += ft_nlen(g->wnd->width);
				g->wnd->height = ft_atoi(str + 2);
			}
			return (id[i][0]);
		}
	while (*str)
		if (!(ft_strchr("012 NEWS", *str++)))
			return (-1);
	return (1);
}

char	**ft_lsttab(t_list *list, u_int16_t rows)
{
	char **map;

	if (!(map = (char **)malloc(sizeof(char *) * (rows + 1))))
		return (NULL);
	rows = 0;
	while (list)
	{
		map[rows++] = list->content;
		list = list->next;
	}
	map[rows] = NULL;
	ft_lstclear(&list, &free);
	return (map);
}

char	**ft_read_map(u_int16_t rows, t_game *g, char *av)
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
			ft_lstadd_back(&list, tmp);
		}
		free(str);
		if (flag == 0)
			break ;
	}
	close(fd);
	return (ft_lsttab(list, rows));
}

#include <stdio.h>
#include <unistd.h>

//int		main(void)
//{
	//u_int16_t rows = 0;
	//static t_game g;
	//static t_window wnd;
	//static t_texture txr;

	//g.wnd = &wnd;
	//g.txr = &txr;
	//char **map = ft_read_map(rows, &g);
	//printf("%s", txr.no);
	//printf("%d", wnd.height);
	//while (*map)
	//{
		//write(1, *map, ft_strlen(*map));
		//write(1, "\n", 1);
		//map++;
	//}
	//return (0);
//}
