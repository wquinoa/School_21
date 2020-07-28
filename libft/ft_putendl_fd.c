/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:24:18 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/22 00:21:27 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char const *s, int fd)
{
	const int i = ft_putstr_fd(s, fd);

	return (i + write(fd, "\n", 1));
}
