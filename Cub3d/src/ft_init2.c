/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:35:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/20 18:47:45 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_player(char dir, int x_pos, int y_pos, t_game *g)
{
	g->plr->x = (x_pos) * HEIGHT;
	g->plr->y = (y_pos) * HEIGHT;
	if (!(g->wnd->width % 16) && !(g->wnd->height % 9))
		g->plr->fov = 84 * M_PI / 180;
	else
		g->plr->fov = 66 * M_PI / 180;
	g->plr->fov_2 = g->plr->fov / 2;
	g->plr->speed = sqrt(HEIGHT) * 2;
	g->plr->deltaray = (float)(g->plr->fov / (g->wnd->width * 1.2));
	if (dir == 'N')
		g->plr->dir = 3 * M_PI_2;
	else if (dir == 'W')
		g->plr->dir = 0;
	else if (dir == 'S')
		g->plr->dir = M_PI_2;
	else if (dir == 'E')
		g->plr->dir = M_PI;
}

int		ft_darken(int color, int16_t i)
{
	if (i > 255)
		i = 255;
	return (color -= (
	(i << 16) * ((color & red) > (255 - i)) |
	(i << 8) * ((color & grn) > (255 - i)) |
	i * ((color & blu) > (255 - i))));
}

uint32_t	ft_calc_color(uint16_t ray, uint8_t h)
{
	uint32_t color;

	color = 0x00e47464;
	if (h == 0)
	{
		if (ray > HEIGHT * 10)
			color += HEIGHT * 10;
		else
			color += ray / 5;
	}
	if (h == 1)
		color = 0x410412 * (ray / 32);
	return (color + ray / 12 * 0x01000000);
}

void	ft_revpaint_tex(t_game *g, int x, int y, int offset, int i)
{
	char	*win;
	char	*tex;

	if (y >= 0 && y < g->wnd->height)
	{
		tex = g->tex->addr + (int)((HEIGHT - i - 1) * g->tex->line_l +
			offset * (g->tex->bpp >> 3));
		win = g->frm->addr + (y * g->frm->line_l + x * (g->frm->bpp >> 3));
		if (g->flags & crt_f)
			*(int *)win = (*(int *)tex | ((g->ray / 6) * 0x01000000));
		else
			*(int *)win = *(int *)tex;
	}
}

int8_t	ft_add_fisheye(uint16_t ray, float k, t_game *g, int offset)
{
	uint16_t		y;
	int				i;
	const uint16_t	x0 = g->x0 - g->wnd->width / g->plr->fov * k;
	const uint16_t	ppu = ((g->wnd->height / FISH * 2) / HEIGHT);

	i = 0;
	y = ray + g->wnd->height / FISH;
	ft_draw_ceil(g, x0, y);
	while (y < g->wnd->height - (ray + g->wnd->height / FISH))
	{
		if (i > 255)
			i = 0;
		ft_paint_tex(g, x0, y++, offset, i++ / ppu);
	}
	ft_draw_floor(g, x0, y);
	if (g->flags & ref_f)
		while (y < g->wnd->height - 2 * ray / 3)
		{
			if (i > 255)
				i = 0;
			ft_blend_tex(g, x0, y++, offset, i++ / ppu);
		}
	return (0);
}

void	ft_add_texture(uint16_t ray, float k, t_game *g, int tex_x)
{
	int				y;
	const uint16_t	x0 = (g->x0 - k * g->wnd->width / g->plr->fov);
	const float		halfwall = HEIGHT / 2 * g->wnd->height / (ray * cos(k));
	int				i;

	i = 0;
	y = g->y0 - halfwall;
	ft_draw_ceil(g, x0, y);
	if (g->flags & hal_f)
	{
		ft_add_fisheye(ray, k, g, tex_x);
		return ;
	}
	while (y < g->y0 + halfwall)
		ft_paint_tex(g, x0, y++, tex_x, i++ / ((halfwall * 2) / HEIGHT));
	if (g->flags & ref_f)
	{
		i = 0;
		while (y < g->y0 + 3 * halfwall - 2)
			ft_blend_tex(g, x0, y++, tex_x, i++ / ((halfwall * 2) / HEIGHT));
	}
	ft_draw_floor(g, x0, y - 5);
}

void	ft_bubble_sort(t_item **array)
{
	uint16_t	passes;
	t_item		*tmp;
	uint16_t	i;

	i = -1;
	passes = 0;
	while (array[++i])
		passes++;
	while (--passes)
	{
		i = -1;
		while (++i < passes)
		{
			if (array[i]->dist > array[i + 1]->dist)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	}
}

void	ft_paint_sprite(t_item item, t_game *g)
{
	int x;
	int y;

	y = -1;
	x = -1;
	write(1, "in\n", 3);
	while (++y < item.size)
	{
		//if (item.x_off + y >= 0 && item.x_off + y < g->wnd->height)
		//{
			while (++x < item.size)
		//		if(item.y_off + x >= 0 && item.y_off + x < g->wnd->width)
					ft_paint(g->frm, x + item.x_off, y + item.y_off, 255);
		//}
	}
}

void	ft_add_sprite(t_item **items, t_game *g)
{
	t_item		*curr;
	t_player	*plr;
	int			i;

	plr = g->plr;
	i = -1;
	while (items[++i])
	{
		curr = items[i];
		curr->dist = ft_max(hypot(plr->x - curr->x, plr->y - curr->y),
		HEIGHT >> 3);
		curr->dir = atan2f(curr->y - plr->y, curr->x - plr->x);
		while (curr->dir - plr->dir > M_PI)
			curr->dir -= 2 * M_PI;
		while (curr->dir - plr->dir < M_PI)
			curr->dir += 2 * M_PI;
		curr->size = ft_min(2000, g->wnd->height / curr->dist);
		curr->x_off = (curr->dir - plr->dir) * g->x0 / plr->fov +
						(g->x0 >> 1) - (curr->size >> 1);
		curr->y_off = g->y0 - (curr->size >> 1);
		ft_paint_sprite(*items[i], g);
	}
	ft_bubble_sort(items);
	i = -1;
//	while (items[++i])
}

void	ft_drawing_handler(float k, t_game *g, t_ray ray)
{
	g->ray = ray.len;
	if ((g->flags & tex_f))
	{
		ft_draw_vline(ray.len, g->plr->dir - k, g);
		return ;
	}
	else if ((int)(ray.x - cos(k)) / HEIGHT == (int)(ray.x / HEIGHT))
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

void	ft_cast_ray(t_game *g, t_player *plr, t_frame *frm)
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
			if ((g->flags & map_f) && ray.len <= HEIGHT * 2)
			{
				ft_mix(frm, ray.x / HEIGHT * (g->wnd->width / (HEIGHT * 2)),
				ray.y / HEIGHT * (g->wnd->width / (HEIGHT * 2)), 0xff7f);
			}
			ray.x += cos(k);
			ray.y += sin(k);
			ray.len++;
		}
		ft_drawing_handler(k, g, ray);
		k += plr->deltaray;
	}
}

void	ft_draw_scene(t_game *g, t_frame *f, t_window *w)
{
	f->img = mlx_new_image(w->mlx, w->width, w->height);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_l, &f->en);
	if (!g->flags)
		ft_minimap(g);
	ft_cast_ray(g, g->plr, g->frm);
	if (g->flags)
		ft_minimap(g);
	ft_add_sprite(g->sprites, g);
	mlx_put_image_to_window(w->mlx, w->win, f->img, 0, 0);
	mlx_destroy_image(w->mlx, f->img);
}

static void	ft_load_textures(t_game *g, t_texture *t)
{
	t_frame	*tex;
	t_frame	**tab[6] = {&g->no, &g->so, &g->ea, &g->we, &g->sp, NULL};
	char	*link[5] = {t->no, t->so, t->ea, t->we, t->sp};
	int8_t	i;
	int16_t	j;

	i = 0;
	while (i < 5)
	{
		j = -1;
		tex = (t_frame *)malloc(sizeof(t_frame));
		tex->img = mlx_xpm_file_to_image(g->wnd->mlx, link[i], &tex->width,
		&tex->height);
		free(link[i]);
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_l,
										&tex->en);
		*tab[i] = tex;
		i++;
	}
}

t_item	**ft_itemtab(t_item *ilist, uint8_t amt)
{
	t_item		**items;
	int			i;

	if (!(items = (t_item**)malloc(sizeof(t_item *) * (amt + 1))))
		exit(0);
	i = -1;
	while (++i < amt)
	{
		items[i] = ilist;
		ilist = ilist->next;
	}
	items[i] = NULL;
	return (items);
}

int		ft_init_item(uint16_t x, uint16_t y, t_item **items)
{
	t_item	*tmp;
	t_item	*new;

	new = (t_item*)malloc(sizeof(t_item));
	tmp = *items;
	ft_bzero(new, sizeof(t_item));
	new->x = x * HEIGHT - (HEIGHT >> 1);
	new->y = y * HEIGHT - (HEIGHT >> 1);
	if (!(*items))
		*items = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_item	**ft_init_sprites(char **map)
{
	uint16_t	x;
	uint16_t	y;
	uint8_t		amt;
	t_item		*ilist;

	y = -1;
	amt = 0;
	ilist = NULL;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '2')
				amt += ft_init_item(x, y, &ilist);
		}
	}
	return (ft_itemtab(ilist, amt));
}

void	ft_init(char *av)
{
	t_game				scene;
	static t_window		window;
	static t_texture	texture;
	static t_player		player;
	static t_frame		f;

	scene.wnd = &window;
	scene.txr = &texture;
	scene.plr = &player;
	scene.frm = &f;
	scene.map = ft_read_map(0, 0, &scene, av);
	scene.sprites = ft_init_sprites(scene.map);
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, \
	"Placeholder name");
	ft_load_textures(&scene, scene.txr);
	ft_draw_scene(&scene, &f, &window);
	mlx_hook(window.win, 2, 0, &key_press, &scene);
	mlx_loop(window.mlx);
}
