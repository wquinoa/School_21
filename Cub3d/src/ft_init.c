/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:35:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/15 21:17:14 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx_o/mlx.h"
#include "../minilibx_o/t_map.h"
#include "../minilibx_o/get_next_line.h"
#include "../minilibx_o/libft.h"

#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int		ft_printf(char *str, ...);

void	ft_init_player(char dir, int x_pos, int y_pos, t_game *g)
{
	g->plr->x = (x_pos) * HEIGHT;
	g->plr->y = (y_pos) * HEIGHT;
	//if (!(g->wnd->width % 16) && !(g->wnd->height % 9))
	//if (g->wnd->width <= g->wnd->height)
	//	g->plr->fov = ((g->wnd->height/g->wnd->width) * 42) * (M_PI / 180);
	//else
		//g->plr->fov = ((g->wnd->width/g->wnd->height) * 66) * (M_PI / 180);
	//else
		g->plr->fov = 66 * M_PI / 180;
	g->plr->fov_2 = g->plr->fov / 2;
	g->plr->speed = sqrt(HEIGHT);
	g->plr->deltaray = (float)(g->plr->fov / (g->wnd->width * 1.1));

	if (dir == 'N')
		g->plr->dir = 3 * M_PI_2;
	else if (dir == 'W')
		g->plr->dir = 0;
	else if (dir == 'S')
		g->plr->dir = M_PI_2;
	else if (dir == 'E')
		g->plr->dir = M_PI;
}

void	ft_paint(t_frame *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
	*(int *)dst = color;
}

void	ft_crt(t_frame *f, t_window *w)
{
	char			*dst;
	int				x = 0;
	int				y = 0;
	const uint8_t	ch = w->width / 160;
	const uint8_t	cw = ch / 2;

	while (y < w->height)
	{
		x = 0;
		while (x < w->width)
		{
			dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
			*(uint32_t *)dst += 0x20000000 * (!(x % cw) || !(y % ch));
			x++;
		}
		y++;
	}
}

int ftBlend(int fg, int bg, uint16_t amount)
{
	const int r = (((fg & red) >> 16) / 64 * amount) +
				(((bg & red) >> 16) / 64 * (64 - amount));
	const int g = (((fg & grn) >> 8) / 64 * amount) +
				(((bg & grn) >> 8) / 64 * (64 - amount));
	const int b = (((fg & blu) >> 0) / 64 * amount) +
				(((bg & blu) >> 0) / 64 * (64 - amount));
	return (((r << 16) & red) | ((g << 8) & grn) | (b & blu));
}

int		ftDarken(int color, int16_t i)
{
	if (i > 255)
		i = 255;
	return(color -=// 0x02000000 * i); /*-=
		(
			(i << 16) * ((color & red) > (255 - i)) |
			(i << 8) * ((color & grn) > (255 - i)) |
			i * ((color & blu) > (255 - i))
		)
	);//*/
}

//int		ftLighten(int color, int16_t i)
//{
	//short diff;

	//if (i > 255)
		//i = 255;
	//diff = 255 - i;
	//return(
		//color += (
		//(i << 16) * ((color & red) < diff) |
		//(i << 8) * ((color & grn) < diff) |
		//(i << 0) * ((color & grn) < diffff : i)
		//)
	//);
//}

void	ft_mix(t_frame *f, int x, int y, int color)
{
	char *dst;
	dst = f->addr + (y * f->line_l + x * (f->bpp / 8));
	*(int*)dst = ftBlend(*(int*)dst, color, 32);
}

void	ft_sun(t_game *g)
{
	float		x;
	float		y;
	float		y0 = 5 * g->wnd->height/ 11;
	const int	s = g->wnd->height / 8;
	float		a;
	uint16_t	i;

	a = 0;
	while (a <= (M_PI * 2))
	{
		i = 0;
		x = g->wnd->width / 2 + cos(g->plr->dir + M_PI_2);
		y = y0;
		while (i < s)
		{
			if ((int)y % 6)
				ft_paint(g->frm, x, y, 0xfc2142 + ((abs((int32_t)(y - y0)) % s)) * (0x0100));
			x += cos(a);
			y += sin(a);
			i++;
		}
		a += (float)(M_PI / 180 / 5);
	}
}

void	ft_floor(t_game *g, uint32_t floor, uint32_t ceil, int flag)
{
	int		x;
	int		y;

	y = -1;
	while (++y <= g->y0)
	{
		x = -1;
		while (++x < g->wnd->width)
			ft_paint(g->frm, x, y, ceil );
		if (g->flags & crt_f && !(y % 6))
			ceil = ftDarken(ceil, 1);
	}
	ft_sun(g);
	if (g->flags & ref_f)
		floor = ftBlend(floor, ceil, 48);
	y = g->wnd->height;
	while (--y > g->y0)
	{
		x = -1;
		while (++x < g->wnd->width)
			ft_paint(g->frm, x, y, floor);
		if (g->flags & crt_f && !(y % 6))
			floor = ftDarken(floor, 1);
	}
}

uint32_t	ft_calc_color(uint16_t ray, t_game *g, uint8_t h)
{
	uint32_t color;

	color = 0x00e47464;

	if (!h)
	{
		if (ray > HEIGHT * 10)
			color += HEIGHT * 10;
		else
			color += ray / 5;
	}
	else
		color = 0x410412 * (ray / 32);
	return (color + ray / 12 * 0x01000000);
}

int8_t	ft_draw_fisheye(uint16_t ray, float k, t_game *g)
{
	uint16_t		x;
	uint16_t		y;
	const uint32_t	color = ft_calc_color(ray, g , 1);
	const uint16_t	x0 = g->x0 - g->wnd->width / g->plr->fov * k;

	y = ray + g->wnd->height / FISH;
	x = x0;
	while (y < g->wnd->height - (ray + g->wnd->height / FISH))
		ft_paint(g->frm, x , y++, color);
	x = x0;
	if (g->flags & ref_f)
	while (y++ < g->wnd->height - 2 * ray / 3)
		ft_mix(g->frm, x, y, color);
	return (0);
}

uint8_t	ft_draw_vline(uint16_t ray, float k, t_game *g)
{
	uint16_t		y;
	const uint16_t	x0 = g->x0 - k * g->wnd->width / g->plr->fov;
	const uint32_t	color = ft_calc_color(ray, g, 0);
	float			halfwall = (HEIGHT >> 1) * g->wnd->height / (ray * cos(k));

	if (g->flags & hal_f)
		return(ft_draw_fisheye(ray, k, g));
	if (halfwall > g->wnd->height >> 1)
		halfwall = g->wnd->height >> 1;
	y = g->y0 - halfwall;
	while (y < g->y0 + halfwall)
		ft_paint(g->frm, x0, y++, color);
	if (!(g->flags & ref_f))
		return (0);
	while (y < g->wnd->height && y < g->y0 + halfwall * 3)
		ft_mix(g->frm, x0, y++, color);
	return(0);
}

void	ftBlendTex(t_game *g, int x, int y, int offset, int i)
{
	char	*win;
	char	*tex;
	int		color;

	if (y >= 0 && y < g->wnd->height)
	{
		tex = g->tex->addr + (int)((HEIGHT - i - 1) * g->tex->line_l +
			offset * (g->tex->bpp / 8));
		win = g->frm->addr + (y * g->frm->line_l + x * (g->frm->bpp / 8));
		color = ftBlend(g->txr->flr, *((int*)tex),
				(i < 56) ? (36 + i / 2) : 64);
		if (g->flags & crt_f)
			*(int *)win = color | ((g->ray / 8) * 0x01000000);
		else
			*(int *)win = color;
	}
}

void	ft_paint_tex(t_game *g, int x, int y, int offset, int i)
{
	char	*win;
	char	*tex;

	if (y >= 0 && y < g->wnd->height)
	{
		tex = g->tex->addr + (int)(i * g->tex->line_l + offset * (g->tex->bpp >> 3));
		win = g->frm->addr + (y * g->frm->line_l + x * (g->frm->bpp >> 3));
		if (g->flags & crt_f)
			*(int *)win = *(int *)tex | ((g->ray / 8) * 0x01000000);
		else
			*(int *)win = *(int *)tex;
	}
}

void	ft_paint_sprite(t_game *g, int x, int y, int offset, int i)
{
	char	*win;
	char	*tex;

	if (y >= 0 && y < g->wnd->height)
	{
		tex = g->tex->addr + (int)(i * g->tex->line_l + offset * (g->tex->bpp >> 3));
		win = g->frm->addr + (y * g->frm->line_l + x * (g->frm->bpp >> 3));
		*(int *)win = *(int *)tex | ((g->ray / 8) * 0x01000000);
	}
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
			*(int *)win = *(int *)tex | ((g->ray / 6) * 0x01000000);
		else
			*(int *)win = *(int *)tex;
	}
}

void	ft_add_texture(uint16_t ray, float k, t_game *g, int offset)
{
	uint16_t		x;
	int				y;
	uint16_t		x0 = (g->x0 - k * g->wnd->width / g->plr->fov);
	const float		halfwall = HEIGHT / 2 * g->wnd->height / (ray * cos(k));
	int i;

	i = 0;
	x = x0;
	y = g->y0 - halfwall;
	while (y <= g->y0 + halfwall - 1)
		ft_paint_tex(g, x, y++, offset, i++ / ((halfwall * 2) / HEIGHT));
	if (!(g->flags & ref_f))
		return;
	i = 0;
	x = x0;
	while (y < g->y0 + 3 * halfwall - 2)
		ftBlendTex(g, x, y++, offset, i++ / ((halfwall * 2) / HEIGHT));
}

void	ft_add_sprite(uint16_t ray, float k, t_game *g, int offset)
{
	uint16_t		x;
	int				y;
	uint16_t		x0 = g->x0 - k * g->wnd->width / g->plr->fov;
	const float		half = HEIGHT / 2 * g->wnd->height / (ray * cos(k));
	int i;

	i = 0;
	x = x0;
	y = g->y0 - half;
	while (y <= g->y0 + half - 1)
		ft_paint_tex(g, x, y++, offset, i++ / ((half * 2) / HEIGHT));
	if (!(g->flags & ref_f))
		return;
	i = 0;
	x = x0;
	while (y < g->y0 + 3 * half - 2)
		ftBlendTex(g, x, y++, offset, i++ / ((half * 2) / HEIGHT));
}

void	ft_drawing_handler(uint16_t ray, float k, t_game *g, float x, float y)
{
	g->ray = ray;
	if ((g->flags & tex_f))
	{
		ft_draw_vline(ray, g->plr->dir - k, g);
		return ;
	}
	else if ((int)(x - cos(k)) / HEIGHT == (int)(x / HEIGHT))
	{
		if ((int)(y - sin(k)) / HEIGHT < (int)(y / HEIGHT))
			g->tex = g->so;
		else if ((int)(y - sin(k)) / HEIGHT > (int)(y / HEIGHT))
			g->tex = g->no;
	}
	else if ((int)(y - sin(k)) / HEIGHT == (int)(y / HEIGHT))
	{
		if ((int)(x - cos(k)) / HEIGHT < (int)(x / HEIGHT))
			g->tex = g->ea;
		else if ((int)(x - cos(k)) / HEIGHT > (int)(x / HEIGHT))
			g->tex = g->we;
	}
	if ((int)(x - cos(k)) / HEIGHT == (int)(x / HEIGHT))
		ft_add_texture(ray, g->plr->dir - k, g, (int)x % HEIGHT);
	else
		ft_add_texture(ray, g->plr->dir - k, g, (int)y % HEIGHT);
}

void	ft_cast_ray(t_game *g, t_player *plr, t_frame *frm)
{
	float			k;
	uint16_t		i;
	float			x;
	float			y;

	k = plr->dir - plr->fov_2;
	while (k < (plr->dir + plr->fov_2))
	{
		i = 0;
		x = plr->x;
		y = plr->y;
		while (g->map[(int)(y / HEIGHT)][(int)(x / HEIGHT)] != '1')
		{
			if (g->flags & map_f)
			{
				ft_mix(frm, x / HEIGHT * (g->wnd->width / (HEIGHT * 2)),
				y / HEIGHT * (g->wnd->width / (HEIGHT * 2)), 0xff7f);
			}
			x += cos(k);
			y += sin(k);
			i++;
		}
		ft_drawing_handler(i, k, g, x, y);
		k += plr->deltaray;
	}

}

void	ft_draw_scene(t_game *g, t_frame *f, t_window *w)
{
	f->img = mlx_new_image(w->mlx, w->width, w->height);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_l, &f->en);
	if (!g->flags)
		ft_minimap(g, f);
	ft_floor(g, g->txr->flr, g->txr->ceil, 3);
	ft_cast_ray(g, g->plr, g->frm);
	//if (g->flags & 1)
		//ft_crt(f, w);
	if (g->flags)
		ft_minimap(g, f);
	mlx_put_image_to_window(w->mlx, w->win, f->img, 0, 0);
	mlx_destroy_image(w->mlx, f->img);
}

static inline char	ft_direction(int key)
{
	const char keys[8] = {s_key, dn, d_key, lf};

	if (ft_memchr(keys, key, 4))
		return (-1);
	else
		return (1);
}


void	ft_wasd(t_game *g, const int8_t dir, int8_t flag, t_trig wasd)
{
	int			i;
	float		*x_pos = &g->plr->x;
	float		*y_pos = &g->plr->y;

	i = -1;
	if (flag == 0)
		while (++i <= g->plr->speed &&
		g->map[((int)(*y_pos + dir * 8 * wasd.sin_v)) / HEIGHT]
		[((int)(*x_pos + dir * 8 * wasd.cos_v)) / HEIGHT] != '1')
		{
			g->plr->x += wasd.cos_v * dir;
			g->plr->y += wasd.sin_v * dir;
		}
	else
		while (++i < g->plr->speed &&
		g->map[((int)(*y_pos + 8 * wasd.sin_v_pi_2)) / HEIGHT]
		[((int)(*x_pos + 8 * wasd.cos_v_pi_2)) / HEIGHT] != '1')
		{
			g->plr->x += wasd.cos_v_pi_2;
			g->plr->y += wasd.sin_v_pi_2;
		}
}

void	key_press2(int key, t_game *g, char dir)
{
	if (key == rt || key == lf || key == d_key || key == a_key)
	{
		g->plr->dir += (ROTATION * dir);
		g->plr->dir -= (g->plr->dir > 2 * M_PI) * 2 * M_PI;
		g->plr->dir += (g->plr->dir < 0) * 2 * M_PI;
	}
	if (key == c_key)
		g->flags ^= crt_f;
	else if (key == h_key)
	{
		g->flags ^= hal_f;
		g->flags |= crt_f;
	}
	else if (key == m_key)
		g->flags ^= map_f;
	else if (key == t_key)
		g->flags ^= tex_f;
	else if (key == pl_key && g->plr->speed < 48)
		g->plr->speed += 4;
	else if (key == mi_key && g->plr->speed > 12)
		g->plr->speed -= 4;
	else if (key == r_key)
		g->flags ^= ref_f;
}

int		key_press(int key, t_game *g)
{
	int			i;
	t_trig		wasd;
	const char	dir = ft_direction(key);

	i = 0;
	ft_bzero(&wasd, sizeof(wasd));
	mlx_clear_window(g->wnd->mlx, g->wnd->win);
	if (key == esc)
		exit(0);
	if (key == w_key || key == up || key == s_key || key == dn)
	{
		wasd.cos_v = cos(g->plr->dir);
		wasd.sin_v = sin(g->plr->dir);
		ft_wasd(g, dir, 0, wasd);
	}
	else if (key == a_key || key == d_key)
	{
		wasd.cos_v_pi_2 = cos(g->plr->dir - dir * M_PI_2);
		wasd.sin_v_pi_2 = sin(g->plr->dir - dir * M_PI_2);
		ft_wasd(g, dir, 1, wasd);
	}
	else
		key_press2(key, g, dir);
	ft_draw_scene(g, g->frm, g->wnd);
	return (0);
}

void	ft_load_textures(t_game *g, t_texture *t)
{
	t_frame	*tex;
	t_frame	**tab[5] = {&g->no, &g->so, &g->ea, &g->we, NULL};
	char	*link[4] = {t->no, t->so, t->ea, t->we};
	int8_t	i;
	int16_t	j;

	i = 0;

	while (i < 4)
	{
		j = -1;
		tex = (t_frame *)malloc(sizeof(t_frame));
		tex->img = mlx_xpm_file_to_image(g->wnd->mlx, link[i], &tex->width,
		&tex->height);
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_l, &tex->en);
		*tab[i] = tex;
		i++;
	}
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
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, \
	"Placeholder name");
	ft_load_textures(&scene, scene.txr);
	ft_draw_scene(&scene, &f, &window);
	mlx_hook(window.win, 2, 0, &key_press, &scene);
	mlx_loop(window.mlx);
}

int main(int argc, char **argv)
{
	if (argc)
		ft_init(argv[1]);
}
