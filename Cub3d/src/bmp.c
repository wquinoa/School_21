/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:48:13 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/01 16:03:15 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_bmp(t_game *g, t_frame *f)
{
	char			*bmp;
	int32_t			num;
	const uint32_t	size = g->wnd->height * g->wnd->width * (f->bpp / 8) + 54;

	!(bmp = (char*)malloc(size)) ? ft_errors(bad_malloc) : 0;
	ft_bzero(bmp, size);
	ft_memcpy(&bmp[0], "BM", 2);
	ft_memcpy(&bmp[2], &size, 4);
	num = 54;
	ft_memcpy(&bmp[10], &num, 4);
	num = 40;
	ft_memcpy(&bmp[14], &num, 4);
	ft_memcpy(&bmp[18], &g->wnd->width, 4);
	num = -g->wnd->height;
	ft_memcpy(&bmp[22], &num, 4);
	num = 1;
	ft_memcpy(&bmp[26], &num, 2);
	ft_memcpy(&bmp[28], &f->bpp, 2);
	ft_memcpy(&bmp[54], f->addr, (size - 54));
	num = open("scr.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	(write(num, bmp, size)) < 0 ? ft_errors(bad_fd) : 0;
	free(bmp);
	close(num);
	ft_errors(bmp_arg);
}
