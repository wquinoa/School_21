/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:32:57 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/09 20:36:03 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*head;
	void	*swap;

	head = *begin_list;
	swap = NULL;
	while (head)
	{
		tmp = head;
		tmp2 = head->next;
		while(tmp2)
		{
			if (cmp(tmp->data, tmp2->data) > 0)
			{
				swap = tmp2->data;
				tmp2->data = tmp->data;
				tmp->data = swap;
			}
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		head = head->next;
	}
}