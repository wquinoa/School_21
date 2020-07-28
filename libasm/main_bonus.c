#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BUFFER_SIZE 512

typedef struct	s_list
{
	void 			*data;
	struct s_list 	*next;
} 				t_list;

int			ft_strcmp(char *s1, char *s2);
int			ft_list_size(t_list *begin_list);
void		ft_list_push_front(t_list **begin, void *data);
void		ft_list_sort(t_list **begin_list, int (*cmp)());
void 		ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
int			ft_atoi_base(char *str, char *base);

int		list_size(t_list *lst)
{
	int		count;
	t_list	*tmp;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void	list_add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

t_list	*list_new(void *data)
{
	t_list		*lst;

	if (!(lst = malloc(sizeof(t_list))))
		return (NULL);
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

int		list_push_front_test(void *new)
{
	t_list	*list;

	list = NULL;
	list_add_back(&list, list_new("wtf"));
	list_add_back(&list, list_new("test"));
	ft_list_push_front(&list, new);
	if (!new && !list->data)
	{
		printf("" GREEN "[OK] " RESET "");
		return (0);
	}
	if (!strcmp(list->data, (char*)new))
	{
		if (!strcmp(list->next->data, "wtf"))
			printf("" GREEN "[OK] " RESET "");
	}
	else
		printf("" RED "[KO] " RESET "");
	ft_list_sort(&list, &ft_strcmp);
	return (1);
}

void	list_size_test(int lst_num)
{
	t_list	*list;

	list = NULL;
	while (lst_num--)
		list_add_back(&list, list_new("a"));
	if (list_size(list) == ft_list_size(list))
		printf("" GREEN "[OK] " RESET "");
	else
		printf("" RED "[KO] " RESET "");
}

int		main(void)
{
	static int i;
	printf("%-16s :  ", "ft_list_size");
	while (i <= 16)
	{
		list_size_test(i);
		i += 8;
	}
	list_size_test(1);
	printf("\n\n");

	printf("%-16s :  ", "ft_push_front");
	list_push_front_test(strdup("aie"));
	list_push_front_test(strdup(""));
	list_push_front_test(strdup("POULOULOU"));
	list_push_front_test(NULL);

	printf("\n\n");
}