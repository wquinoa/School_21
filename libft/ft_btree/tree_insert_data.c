/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insert_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:01:55 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/31 13:36:15 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	tree_insert_data(t_btree **root, void *item, int (*cmp)(void *, void *))
{
	if (!root)
	{
		*root = tree_create_node(item);
		return ;
	}
	if (cmp(item, (*root)->item) < 0)
	{
		if ((*root)->left)
			tree_insert_data(&(*root)->left, item, cmp);
		else
			(*root)->left = tree_create_node(item);
	}
	else
	{
		if ((*root)->right)
			tree_insert_data(&(*root)->right, item, cmp);
		else
			(*root)->right = tree_create_node(item);
	}
}