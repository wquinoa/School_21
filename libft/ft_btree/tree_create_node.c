/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 12:41:12 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/31 13:52:40 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_btree		*tree_create_node(void *item)
{
    t_btree *node;

    node = ft_calloc(1, sizeof(t_btree));
    node ? node->item = item : 0;
    return (node);
}