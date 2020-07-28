;int		ft_lstsize(t_list *lst)
;{
	;int		i;

	;i = 0;
	;tmp = lst;
	;while (tmp && ++i)
		;tmp = tmp->next;
	;return (i);
;}

section .text
	global _ft_list_size

_ft_list_size:
			mov		rax, 0			;int i = 0;

_while_lst:							;while (1)
			cmp		rdi, 0			;	if (lst == NULL)
			jz		_return_size	;		return (i);
			mov		rdi, [rdi+8]	;	lst = lst->next;
			inc		rax				;	i++;
			jmp		_while_lst

_return_size:
			ret
