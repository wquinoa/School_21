;void 		ft_list_remove_if
;(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

section .text
	global _ft_list_remove_if

_ft_list_remove_if:
			push	rcx				;save free
			cmp		rdi, 0
			jz		_retur
			cmp		rsi, 0
			jz		_retur
			mov		r10, [rdi]		;r10 = *begin
			mov		r11, rdx		;r11 = cmp
			;push	rsi				;save dataref
			mov		r12, r10		;r12 = begin
			mov		r13, [r12+8]	;r13 = begin->next

_while_l:
			cmp		r13, 0
			jz		_retur
			mov		rdi, [r12]
			call	r11
			cmp		rax, 0
			jz		_remove
_move_l:
			mov		r12, [r12 + 8]
			mov		r13, [r13 + 8]
			jmp		_while_l

_retur:
			pop		rcx
			ret

_remove:

