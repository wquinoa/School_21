/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:57:41 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/15 11:57:27 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	if (!lst)
	{
		ft_putendl_fd("[ \033[31;1mnull\033[0m ]\n", 1);
		return ;
	}
	ft_putstr_fd("\n \033[32;1mnew\033[0m ", 1);
	while (tmp)
	{
		ft_putstr_fd("\033[0m->[ ", 1);
		if (tmp->next == NULL)
			ft_putstr_fd("\033[34;1m", 1);
		else
			ft_putstr_fd("\033[34m", 1);

		ft_putstr_fd((char *)(tmp)->content, 1);
		tmp = tmp->next;
		ft_putstr_fd(" \033[0m]", 1);
	}
	ft_putendl_fd("\033[31m->[x]\033[0m\n", 1);
}
