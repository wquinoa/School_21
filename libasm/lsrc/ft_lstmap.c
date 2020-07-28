/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 06:20:19 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/07 01:11:02 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*curr_elem;
	t_list	*next_elem;

	if (!lst || !(new = ft_lstnew(f(lst->data))))
		return (NULL);
	next_elem = new;
	lst = lst->next;
	while (lst)
	{
		if (!(curr_elem = ft_lstnew(f(lst->data))))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		next_elem->next = curr_elem;
		next_elem = next_elem->next;
		lst = lst->next;
	}
	return (new);
}
