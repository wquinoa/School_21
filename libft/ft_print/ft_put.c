/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:10:17 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/28 18:33:18 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_putchar(char c)
{
	return (ft_putchar_fd(c, 1));
}

int		ft_putstr(char const *s)
{
	return (ft_putstr_fd(s, 1));
}

int		ft_putendl(char const *s)
{
	return (ft_putendl_fd(s, 1));
}

int		ft_putnbr(int n)
{
	return (ft_putnbr_fd(n, 1));
}
