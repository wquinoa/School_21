/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_flags.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 14:52:15 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/02 04:26:13 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_FLAGS_H
# define P_FLAGS_H

enum		e_parse
{
	bad_malloc = -1,
	bad_fd = -2,
	bad_map = -3,
	dup_tex = -4,
	bad_tex = -5,
	bad_color = -6,
	dup_res = -7,
	dup_col = -8,
	bmp_arg = -9,
	bad_res = -11,
	bad_sym = -12,
	bad_args = -10,
	res_f = 1,
	cel_f = 2,
	flo_f = 4,
	pla_f = 8,
	sav_f = 32
};

#endif
