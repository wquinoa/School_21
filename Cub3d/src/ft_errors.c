/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 14:16:13 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/24 15:39:59 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_errors(char error_code)
{
	(error_code == bad_malloc) ? write(2, "Malloc failed.\n", 15) : 0;
	(error_code == bad_fd) ?
	write(2, "File not found/invalid file type.\n", 34) : 0;
	(error_code == bad_map) ? write(2, "Bad map format.\n", 16) : 0;
	(error_code == dup_tex) ? write(2, "Duplicate textures.\n", 20) : 0;
	(error_code == dup_res) ? write(2, "Duplicate resolutions.\n", 23) : 0;
	(error_code == dup_col) ? write(2, "Duplicate colors.\n", 18) : 0;
	(error_code == bad_tex) ? write(2, "Bad texture file.\n", 18) : 0;
	(error_code == bad_color) ? write(2, "Bad color format.\n", 18) : 0;
	(error_code == bad_sym) ? write(2, "Some lines are invalid.\n", 25) : 0;
	(error_code == bad_args) ? write(2, "Invalid main arguments.\n", 25) : 0;
	write(2, "Exiting cub3d...\n", 17);
	exit(0);
}
