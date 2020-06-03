/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:20:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/03 17:07:17 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "../minilibx_o/mlx.h"
# include "../minilibx_o/get_next_line.h"
# define HEIGHT 300
# define ROTATION 0.08
# define SQ(x) (x * x)

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
	up = 126,
	dn = 125,
	lf = 123,
	rt = 124,
};


typedef struct 			s_player
{
	double				x;
	double				y;
	double				dir;
	double				fov;
	double				speed;
}						t_player;

typedef struct			s_texture
{
	char				*no;
	char				*so;
	char				*ea;
	char				*we;
	char				*sp;
	int					*flr;
	int					*ceil;
}						t_texture;

typedef struct			s_frame
{
	void				*img;
	void				*mmap;
	char				*addr;
	int					bpp;
	int					line_l;
	uint8_t				scale;
	int					en;
}						t_frame;

typedef struct			s_window
{
	void				*mlx;
	void				*win;
	uint16_t			width;
	uint16_t			height;
	struct s_player		*player;
}						t_window;

typedef struct			s_game
{
	char				**map;
	struct s_frame		*frm;
	struct s_player		*plr;
	struct s_window		*wnd;
	struct s_texture	*txr;
}						t_game;

char					**ft_read_map(u_int16_t rows, t_game *g, char *av);
void					ft_minimap(t_game *g, t_frame *f);
void					ft_init_player(char dir, int x_pos, int y_pos, t_game *g);
void					ft_paint(t_frame *f, int x, int y, int color);

#endif