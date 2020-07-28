;cchar	*ft_strdup(const char * rdi)

section .text
	global _ft_strdup
	extern _malloc
	extern _ft_strlen
	extern _ft_strcpy

_ft_strdup:
			push	rdi			; char *tmp = rdi;
			call	_ft_strlen	; rax = ft_strlen(rdi);
			inc		rax			; rax += 1; // for malloc
			mov		rdi, rax	; 
			call	_malloc		; rax = malloc(rax);
			pop		rsi			; rsi = tmp;
			cmp		rax, 0		; if (rax == NULL)
			jz		_ret_dup	;		 return(rax);
			mov     rdi, rax	; 
			call	_ft_strcpy	; rax = ft_strcpy(rdi, rsi);

_ret_dup:
			ret