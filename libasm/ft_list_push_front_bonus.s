;  void ft_list_push_front(t_list **begin_list, void *data);

section .text
	global _ft_list_push_front
	extern _malloc

_ft_list_push_front:
			cmp			rdi, 0				;if (!begin)
			jz			_ret_s				;	return ;
			cmp			rsi, 0				;if (!data)
			jz			_ret_s				;	return ;
			mov			r13, rsi			;save data
			mov			r14, rdi			;save begin
			mov			rdi, 16				;sizeof(t_list);
			call		_malloc				;new = malloc(sizeof(t_list));
			cmp			rax, 0				;if (!new)
			jz			_ret_s				;	ruturn ;
			mov			r12, [r14]			;t_lsit *tmp = *begin;
			mov			[rax], r13			;new->data = data;
			mov			[rax + 8], r12		;new->next = *tmp;
			mov			[r14], rax			;(t_list**)begin = &new;

_ret_s:
			ret
