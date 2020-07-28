/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:05:26 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/09 19:49:46 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/errno.h>

typedef	struct			s_list
{
	void				*data;
	struct s_list		*next;
}						t_list;

char					*ft_strcpy(char *dst, const char *src);
char					*ft_strdup(const char *src);
int						ft_strcmp(const char *dst, const char *src);
size_t					ft_strlen(const char *str);
ssize_t					ft_write(int fildes, const void* buf, size_t nbyte);
ssize_t					ft_read(int fildes, const void* buf, size_t nbyte);

/*
** Bonus part
*/

int						ft_list_size(t_list *head);
void					ft_list_push_front(t_list **begin_list, void *data);
void					ft_list_sort(t_list **begin_list, int (*cmp)());


t_list					*ft_lstnew(void *data);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lst_sort(t_list **begin_list, int (*cmp)());
void					ft_lstclear(t_list **lst, void (*del)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
												void (*del)(void *));

#endif
