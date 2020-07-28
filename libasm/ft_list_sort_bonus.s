;void	ft_list_sort(t_list **begin, int (*cmp())
;rax						rdi		,		rsi
;	compare 2 elems
;	swap &data if needed

section .text
	global _ft_list_sort
	extern _ft_list_size

; begin
;	|
; data, next ([begin], [begin + 8])
;		  |
;		data, next ([next], [next + 8])
;				|
;				NULL ([next])

_ft_list_sort:
			cmp		rdi, 0			;
			jz		_ret_s			;
			cmp		rsi, 0			;
			jz		_ret_s			;
			mov		r10, [rdi]		; r10 = *begin;
			cmp		r10, 0			; if (*begin == NULL)
			jz		_ret_s			;	return ;
			mov		r11, rsi		; r11 = cmp;
			mov		rdi, r10		; rdi = begin;
			call	_ft_list_size	;
			mov		r14, rax		; int passes = ft_list_size(begin);

_loop_out:
			dec		r14				; passes--
			cmp		r14, 0			; if (passes == 0)
			jz		_ret_s			;	return ;
			mov		r15, r14		; i = passes
			mov		rdi, r10		; rdi = *begin;
			mov		rsi, [r10 + 8]	; rsi = begin->next;
			cmp		rsi, 0			; if (begin->next == NULL)
			jz		_ret_s			; 	return ;

_loop_in:
			cmp		r15, 0			; if (i = 0)
			je		_loop_out		; 	break ;
			push	rdi				; save begin
			push	rsi				; save begin->next
			mov		rdi, [rdi]		; rdi = data1;
			mov		rsi, [rsi]		; rsi = data2;
			call	r11				; strcmp(data1, data2);
			pop		rsi				; rsi = begin->next;
			pop		rdi				; rdi = begin;
			cmp		rax, 0			; if (data1 > data2)
			jg		_swap			;	swap(data1, data2);

_reloop:
			mov		rdi, [rdi + 8]	; rdi = rdi->next;
			mov		rsi, [rsi + 8]	; rsi = rsi->next;
			dec		r15
			jmp		_loop_in

_swap:
			mov		r12, [rdi]
			mov		r13, [rsi]
			mov		[rdi], r13
			mov		[rsi], r12
			jmp		_reloop

_ret_s:
			ret