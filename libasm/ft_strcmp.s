; char	*ft_strcmp(cosnt char *s1, constchar *s2)
; 	char *rdi = s1;
; 	char *rsi = s2;

section .text
	global _ft_strcmp

_ft_strcmp:
			mov		r8, -1				;	i = -1;
			mov		rax, 0				;	initialize registers-
			mov		rcx, 0				;	to 0 before using

_loop:									;while (1)
			inc		r8					;	++i;
			mov		al, [rdi + r8]		;	char a = s1[i];
			mov		cl, [rsi + r8]		;	char c = s2[i];
			cmp		al, byte 0			;	if (a == '\0')
			je		_end				;		return
			cmp		al, cl				;	if (a == c)
			je		_loop				;		loop again

_end:
			sub		rax, rcx			;	return (a - c);
			ret
