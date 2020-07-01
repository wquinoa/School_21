/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 20:00:30 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 16:03:28 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ft_check_res(t_window *wnd)
{
	int sx;
	int sy;

	mlx_get_screen_size(wnd->mlx, &sx, &sy);
	wnd->width = (wnd->width < sx) ? wnd->width : sx;
	wnd->height = (wnd->height < sy) ? wnd->height : sy;
}

void		ft_clear(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

static char	**ft_lsttab(t_list *list, u_int16_t rows, uint16_t col, t_game *g)
{
	char	**map;
	t_list	*head;
	short	i;

	if (!(map = (char **)malloc(sizeof(char *) * ((rows += 2) + 1))))
		ft_errors(bad_malloc);
	i = -1;
	col += 2;
	head = list;
	while (++i < rows)
	{
		map[i] = ft_calloc(1, col + 1);
		ft_memset(map[i], ' ', col);
		if (list)
		{
			ft_strlcpy(map[i] + 1, list->content, col - 1);
			free(list->content);
			list = list->next;
		}
	}
	ft_clear(head);
	map[i] = NULL;
	ft_mapval(map, rows, g);
	return (map);
}

char		**ft_read_map(uint16_t rows, uint16_t lng, t_game *g, char *av)
{
	const int		fd = open(av, O_RDONLY);
	t_list			*list;
	t_list			*tmp;
	char			*str;
	int				flag;

	list = NULL;
	while ((flag = get_next_line(fd, &str)) >= 0)
	{
		if (ft_strval(str, g) == 1)
		{
			if (!(tmp = ft_lstnew(ft_strdup(str))))
				ft_errors(bad_malloc);
			rows++;
			lng = lng > ft_strlen(str) ? lng : ft_strlen(str);
			ft_lstadd_back(&list, tmp);
		}
		free(str);
		if (flag == 0)
			break ;
	}
	close(fd);
	if (flag == -1)
		ft_errors(bad_fd);
	return (ft_lsttab(list, rows, lng, g));
}
