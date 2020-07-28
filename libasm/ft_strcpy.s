; char	*ft_strcpy(char *dst, char *src)
; 	char *rdi = dst;
; 	char *rsi = src;

section .text
	global _ft_strcpy

_ft_strcpy:
			mov		rax, 0				;int rax = 0;

_strcpy_loop:						;while (1)
			mov		cl, byte [rsi+rax]	;	tmp = src[i];
			cmp		cl, 0				;	if (tmp == '\0')
			je		_strcpy_end			;		return (dst);
			mov		byte [rdi+rax], cl	;	dst[i] = tmp;
			inc		rax					;	rax++;
			jmp		_strcpy_loop

_strcpy_end:
			mov		rax, rdi			;	return (dst);
			ret
