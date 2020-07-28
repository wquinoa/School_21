; nasm -fmacho64 ft_strlen.s && gcc main.c ft_strlen.o && ./a.out
; size_t	ft_strlen(char *str)

section .text
	global _ft_strlen				;char *rdi = str;

_ft_strlen:
		mov		rax, 0				;int rax = 0;
		cmp		rdi, 0				;if (str == NULL)
		je		_strlen_end			;	return (0)

_while_loop:						;while (1)
		cmp		[rdi+rax], byte 0	;	if (*(str + rax) == '\0')
		je		_strlen_end			;		break ;
		inc		rax					;	rax++;
		jmp		_while_loop

_strlen_end:
		ret							;return (rax);
