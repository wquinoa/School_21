/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texncol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:31:25 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 04:44:38 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/p_flags.h"

static char	*ft_precheck(char *link)
{
	int16_t		i;

	i = 0;
	while (*link && ft_isspace(*link))
		link++;
	while (link[i] && !(ft_isspace(link[i])))
		i++;
	link[i] = '\0';
	i = open(link, O_RDONLY);
	close(i);
	if (!ft_strnstr(link, ".xpm", ft_strlen(link)) || i == -1)
		ft_errors(bad_tex);
	return (link);
}

int8_t		ft_get_link(const char *c, char *str, t_game *g)
{
	char		*link;

	link = str + 2;
	link = ft_precheck(link);
	if (*c == 'N' && !(g->txr->no))
		g->txr->no = ft_strdup(link);
	else if (*c == 'S' && *(c + 1) == 'O' && !(g->txr->so))
		g->txr->so = ft_strdup(link);
	else if (*c == 'S' && *(c + 1) == ' ' && !(g->txr->sp))
		g->txr->sp = ft_strdup(link);
	else if (*c == 'E' && !(g->txr->ea))
		g->txr->ea = ft_strdup(link);
	else if (*c == 'W' && !(g->txr->we))
		g->txr->we = ft_strdup(link);
	else
		ft_errors(dup_tex);
	return (1);
}

static void	ft_write_color(char c, int a, t_game *g)
{
	if (c == 'F' && !(g->flags & flo_f))
	{
		g->flags |= flo_f;
		g->txr->flr = a;
	}
	else if (c == 'C' && !(g->flags & cel_f))
	{
		g->flags |= cel_f;
		g->txr->ceil = a;
	}
	else
		ft_errors(dup_col);
}

int8_t		ft_get_color(char c, char *str, t_game *g)
{
	int			tmp;
	char		*tmps;
	int			a;
	int8_t		i;
	char		**channels;

	str = ft_strswap(str, ',', ' ');
	!(channels = ft_split(str, ' ')) ? ft_errors(bad_malloc) : 0;
	i = 0;
	a = 0;
	while (channels[++i])
	{
		tmp = ft_atoi(channels[i]);
		if (!(tmps = ft_strtrim(channels[i], " 0123456789")))
			ft_errors(bad_malloc);
		tmps[0] != '\0' ? ft_errors(bad_color) : 0;
		free(tmps);
		(tmp < 0 || tmp > 255) ? ft_errors(bad_color) : 0;
		a |= tmp << (3 - i) * 8;
	}
	i != 4 ? ft_errors(bad_color) : 0;
	ft_write_color(c, a, g);
	ft_tabclear(channels);
	return (1);
}
