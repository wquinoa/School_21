/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:27:54 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/04 01:06:23 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next_elem;

	next_elem = *lst;
	while (next_elem)
	{
		tmp = next_elem;
		next_elem = tmp->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
