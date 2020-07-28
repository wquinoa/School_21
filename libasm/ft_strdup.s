
section .text
	global _ft_strdup
	extern _ft_strlen
	extern _ft_strcpy
	extern _malloc

_ft_strdup:
			push		rdi				; stack : &src;
			call		_ft_strlen		; rax = ft_strlen(rdi);
			mov			rdi, rax		; arg1 = rax;
			inc			rdi				; arg1++ for malloc;
			call		_malloc
			pop			rsi				; arg2 = &src;
			cmp			rax, 0			; if (!malloc(sizeof(arg1)))
			je			_strdup_end		;	return ;
			mov			rdi, rax		; arg1 = memory;
			call		_ft_strcpy		; ft_strcpy(arg1, arg2)

_strdup_end:
			ret
