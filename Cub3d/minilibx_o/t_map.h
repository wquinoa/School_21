/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:20:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/02 00:33:01 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H
# define SCALE 16
# define SPEED 4
# define ROTATION 0.175
# define SQRT(x) (int)sqrt(x)
# define SQ(x) (x * x)
# define COL(x) (int)(x / SCALE)
# include "libft.h"
# include <string.h>
# include <fcntl.h>

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
	t_uint16			x;
	t_uint16			y;
	double				dir_x;
	double				dir_y;
	double				dir;
}						t_player;

typedef struct			s_window
{
	t_list				*map;
	void				*mlx;
	void				*win;
	uint16_t			width;
	uint16_t			height;
	struct s_player		*player;
}						t_window;

typedef struct			s_texture
{
	char				*no;
	char				*so;
	char				*ea;
	char				*we;
	char				*sp;
	int16_t				*flr;
	int16_t				*ceil;
}						t_texture;


typedef struct			s_game
{
//	t_list				*map;
	char				**map;
	struct s_player		*plr;
	struct s_window		*wnd;
	struct s_texture	*txr;
}						t_game;

#endif