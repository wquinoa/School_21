;int	*ft_list_size(t_list *begin);

section .text
	global _ft_list_size

_ft_list_size:
			mov		rax, 0			;int i = 0;

_list_loop:
			cmp		rdi, 0			;if (begin == NULL)
			je		_ret_size		;	return (i);
			inc		rax				;i++;
			mov		rdi, [rdi + 8]	;begin = begin->next;
			jmp		_list_loop

_ret_size:
			ret