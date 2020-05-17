/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list-visualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:09:16 by wquinoa           #+#    #+#             */
/*   Updated: 2020/05/17 18:16:51 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

/*
**	Mostly works on your libft, so compile it with your lib.
**	./a.out new [content] will visualize your lstnew.
**	./a.out add [content] will visualize all of your bonus functions.
*/

void	test_iter(void *s)
{
	ft_putstr_fd(" ", 1);
	ft_putstr_fd((char *)s, 1);
}

void	ft_swap(char *a, char *b)
{
	char c;

	c = *a;
	*a = *b;
	*b = c;
}

char	*ft_strrev(char *s)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	while (len >= 0 && i < len)
		ft_swap(&s[i++], &s[--len]);
	return (s);
}

void	*ft_contentdup(void *content)
{
	char		*dst;
	char		*d;
	const char	*tmp = (char *)content;

	if (!(dst = (char *)malloc((ft_strlen(content) + 1) * sizeof(char))))
		return (NULL);
	d = dst;
	while (*tmp)
		*(dst++) = *(tmp++);
	*dst = '\0';
	return (ft_strrev(d));
}

void	ft_putlst(t_list *lst)
{
	t_list *tmp = lst;
	if (!lst)
	{
		ft_putendl_fd("[ \033[31;1mX\033[0m ]\n", 1);
		return;
	}
	ft_putstr_fd("\n \033[32;1mnew\033[0m ", 1);
	while (tmp)
	{
		ft_putstr_fd("\033[0m->[ " , 1);
		if (tmp->next == NULL)
			ft_putstr_fd("\033[34;1m", 1);
		else
			ft_putstr_fd("\033[34m", 1);
		ft_putstr_fd((char *)(tmp)->content, 1);
		//ft_putstr_fd("\033[0m | \033[32mnext\033[0m ]-> \033[0m[ ", 1);
		tmp = tmp->next;
		ft_putstr_fd(" \033[0m]" , 1);
	}
	ft_putendl_fd("\033[31m->[x]\033[0m\n", 1);
}

void	t_lstnew(void *content)
{
	char	*dst;
	t_list	*new;

	ft_putendl_fd("\n\033[35mft_lstnew(argv[2])\033[0m:", 1);
	if (!(dst = ft_strdup(content)))
	{
		ft_putstr_fd("contentdup failed :S", 1);
		return ;
	}
	if (!(new = ft_lstnew(dst)))
	{
		ft_putstr_fd("null on lstnew.", 1);
		return ;
	}
	else
		ft_putlst(new);
}

void	t_lstadd_back(t_list *new, void **content)
{
	t_list *back;

	ft_putendl_fd("\n\033[35mft_lstaddback(argv[3:])\033[0m:", 1);
	for (int i = 0; content[i] ; i++)
	{
		if (!(back = ft_lstnew(ft_strdup(content[i]))))
		{
			ft_putendl_fd("ft_strdup failed", 1);
			return;
		}
		ft_lstadd_back(&new, back);
		back = NULL;
		ft_putlst(new);
	}
}

void	t_lstadd_front(t_list **new, void *newc)
{
	t_list	*front;

	ft_putendl_fd("\n\033[35mft_lstadd_front(new, argv[3])\033[0m:\n", 1);
	if(!(front = (ft_lstnew(ft_strdup(newc)))))
	{
		ft_putstr_fd("It failed. How?", 1);
		ft_lstclear(new, &free);
		return ;
	}
	ft_lstadd_front(new, front);
}

t_list	*t_lstdelone(t_list *new)
{
	t_list *tmp;

	ft_putendl_fd("\n\033[35mft_lstdelsone(new, argv[3])\033[0m:", 1);
	tmp = new;
	new = new->next;
	ft_putendl_fd(" new = new->next", 1);
	ft_lstdelone(tmp, free);
	ft_putlst(new);
	return (new);
}

void	t_lstadd(void *newc, void **content)
{
	t_list	*new;
	t_list	*res;

	if(!(new = (ft_lstnew(ft_strdup(newc)))))
		return ;
	t_lstnew(newc);
	t_lstadd_back(new, content);
	t_lstadd_front(&new, newc);
	ft_putlst(new);
	new = t_lstdelone(new);
	ft_putendl_fd("\n\033[35mft_lstiter(new, &ft_putstr_fd)\033[0;1m:\n", 1);
	ft_lstiter(new, &test_iter);
	ft_putendl_fd("\033[0m", 1);
	ft_putendl_fd("\n\033[35mft_lstmap(new, &ft_contentrev, &free)\033[0;1m:\n", 1);
	if (!(res = ft_lstmap(new, (void *)&ft_contentdup, &free)))
		return;
	ft_lstiter(res, &test_iter);
	ft_putendl_fd("\n", 1);
	ft_putendl_fd("\n\033[35mft_lstclear(new, &ft_contentrev, &free)\033[0m:\n", 1);
	ft_lstclear(&res, &free);
	ft_putlst(res);
	ft_lstclear(&new, &free);
	ft_putlst(new);
}

int		main(int argc, char **argv)
{
	if (argc >= 2)
		if ((strcmp(argv[1], "new") == 0) || (strcmp(argv[1], "del") == 0))
			t_lstnew((void *)argv[2]);
	if (argc >= 4)
		if (strcmp(argv[1], "add") == 0)
			t_lstadd((void *)argv[2], (void **)&argv[3]);
}