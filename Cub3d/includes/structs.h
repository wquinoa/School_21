/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 15:01:02 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/30 04:11:18 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct			s_player
{
	float				x;
	float				y;
	float				dir;
	float				fov;
	float				fov_2;
	float				deltaray;
	uint8_t				dm;
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
	int32_t				width;
	int32_t				height;
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

typedef struct			s_item
{
	float				x;
	float				y;
	float				dist;
	float				dir;
	uint16_t			size;
	uint16_t			x_off;
	uint16_t			y_off;
	uint8_t				ex;
	struct s_item		*next;
}						t_item;

#endif
