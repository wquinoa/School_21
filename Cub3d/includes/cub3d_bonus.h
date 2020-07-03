/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:20:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 08:38:37 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "p_flags.h"
# include "structs.h"
# include "../SDL2-A/src/audio.h"
# include "../minilibx_mms/mlx.h"
# define HEIGHT 64
# define ROTATION 0.12
# ifndef BONUS
#  define BONUS 1
# endif

enum					e_key
{
	esc = 53,
	w_key = 13,
	a_key = 0,
	s_key = 1,
	d_key = 2,
	c_key = 8,
	up = 126,
	dn = 125,
	lf = 123,
	rt = 124,
	alp = (255 << 24),
	red = (255 << 16),
	grn = (255 << 8),
	blu = 255,
	crt_f = 1,
};

typedef struct			s_game
{
	char				**map;
	struct s_frame		*frm;
	struct s_player		*plr;
	struct s_window		*wnd;
	struct s_texture	*txr;
	t_item				**sprites;
	uint16_t			depth[6000];
	uint16_t			x0;
	uint16_t			xcur;
	uint16_t			mcur;
	uint16_t			y0;
	uint8_t				items;
	uint16_t			ray;
	uint32_t			flags;
	t_frame				*tex;
	t_frame				*no;
	t_frame				*so;
	t_frame				*ea;
	t_frame				*we;
	t_frame				*es;
	t_frame				*sp;
}						t_game;

/*
**	Init package
*/

void					ft_init(char **av, int ac);
void					ft_init2(char *av, int save);
char					**ft_read_map(uint16_t rows, uint16_t longest,
												t_game *g, char *av);
void					ft_check_res(t_window *wnd, char *str);
t_item					**ft_init_sprites(char **map);
void					ft_minimap(t_game *g);
int8_t					ft_get_color(char c, char *str, t_game *g);
int8_t					ft_get_link(const char *c, char *str, t_game *g);
void					ft_mapval(char **map, uint16_t rows, t_game *g);
int8_t					ft_strval(char *str, t_game *g);

/*
**	The engine
*/

void					ft_draw_scene(t_game *g, t_frame *f, t_window *w);
void					ft_cast_ray(t_game *g, t_player *plr);
int						key_press(int key, t_game *g);
int						ft_move_mouse(int x, int y, t_game *g);

/*
**	Drawing package
*/

void					ft_add_sprite(t_item **items, t_game *g);
void					ft_paint(t_frame *f, int x, int y, int color);
void					ft_paint_tex(t_game *g, t_ray pt, int offset, int i);
void					ft_blend_tex(t_game *g, t_ray pt, int offset, int i);
int						ft_darken(int color, int16_t i);

void					ft_draw_floor(t_game *g, int x0, int end);
void					ft_draw_ceil(t_game *g, int x0, int end);

/*
**	Utilities
*/

void					ft_init_sound(t_game *g, t_frame *es);
void					ft_bmp(t_game *g, t_frame *f);
void					ft_errors(char error_code);
void					ft_countdown(void);
int						ft_exit(void);

#endif
