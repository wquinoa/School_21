/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:05:20 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/03 04:28:37 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list *new_list;

	if (!(new_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}
