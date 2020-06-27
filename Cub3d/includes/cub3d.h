/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:20:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/21 13:51:24 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# define HEIGHT 64
# define FISH 8
# define ROTATION 0.12

typedef unsigned short		t_uint16;
typedef unsigned long long	t_uint64;
typedef long long			t_int64;
typedef unsigned char		t_uint8;

enum					e_key
{
	esc = 53,
	w_key = 13,
	a_key = 0,
	s_key = 1,
	d_key = 2,
	c_key = 8,
	h_key = 4,
	m_key = 46,
	t_key = 17,
	r_key = 15,
	pl_key = 24,
	mi_key = 27,
	up = 126,
	dn = 125,
	lf = 123,
	rt = 124,
	alp = (255 << 24),
	red = (255 << 16),
	grn = (255 << 8),
	blu = 255,
	crt_f = 1,
	hal_f = 2,
	map_f = 4,
	tex_f = 8,
	ref_f = 16,
};

typedef struct 			s_player
{
	float				x;
	float				y;
	float				dir;
	float				fov;
	float				fov_2;
	float				deltaray;
	uint8_t				speed;
}						t_player;

typedef struct			s_texture
{
	char				*no;
	char				*so;
	char				*ea;
	char				*we;
	char				*sp;
	int					flr;
	int					ceil;
}						t_texture;

typedef struct			s_frame
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_l;
	int					en;
	uint8_t				scale;
	int					width;
	int					height;
}						t_frame;

typedef struct			s_window
{
	void				*mlx;
	void				*win;
	uint16_t			width;
	uint16_t			height;
	struct s_player		*player;
}						t_window;

typedef struct			s_trig
{
	float				cos_v;
	float				sin_v;
	float				cos_v_pi_2;
	float				sin_v_pi_2;
}						t_trig;

typedef struct			s_ray
{
	int					flag;
	float				x;
	float				y;
	float				len;
}						t_ray;

typedef struct			s_vline
{
	int					x;
	int					y;
	int					tex_x;
	int					tex_y;
	float				half;
}						t_vline;

typedef struct			s_item
{
	float				x;
	float				y;
	float				dist;
	float				dir;
	uint16_t			size;
	uint16_t			x_off;
	uint16_t			y_off;
	struct s_item		*next;
}						t_item;

typedef struct			s_game
{
	char				**map;
	struct s_frame		*frm;
	struct s_player		*plr;
	struct s_window		*wnd;
	struct s_texture	*txr;
	struct s_ray		*rayy;
	t_item				**sprites;
	uint16_t			depth[6000];
	uint16_t			x0;
	uint16_t			y0;
	uint16_t			ray;
	uint32_t			flags;
	t_frame				*tex;
	t_frame				*no;
	t_frame				*so;
	t_frame				*ea;
	t_frame				*we;
	t_frame				*sp;
}						t_game;


char					**ft_read_map(uint16_t rows, uint16_t longest, t_game *g, char *av);
void					ft_minimap(t_game *g);
void					ft_init_player(char dir, int x_pos, int y_pos, t_game *g);
void					ft_draw_scene(t_game *g, t_frame *f, t_window *w);
int						key_press(int key, t_game *g);

uint32_t				ft_calc_color(uint16_t ray, uint8_t h);
int						ft_darken(int color, int16_t i);

uint8_t					ft_draw_vline(uint16_t ray, float k, t_game *g);

void					ft_paint(t_frame *f, int x, int y, int color);
void					ft_mix(t_frame *f, int x, int y, int color);
void					ft_paint_tex(t_game *g, int x, int y, int offset, int i);
void					ft_blend_tex(t_game *g, int x, int y, int offset, int i);

void					ft_draw_floor(t_game *g, int x0, int end);
void					ft_draw_ceil(t_game *g, int x0, int end);

#endif