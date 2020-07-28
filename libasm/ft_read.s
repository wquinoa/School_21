;ssize_t read(int fd, const void *buf, size_t nbyte)
;int rdi = fd;
;char* rsi = buf;
;int rdx = nbyte;

section .text
	global _ft_read
	extern ___error

_ft_read:
			mov			rax, 0x2000003	; call read
			syscall
			jb			_error			; if (syscall < 0)
			ret							; else return
_error:
			push		rax				; save value returned by syscall
			call		___error		; call error. rax = &errno
			pop			r8				; retrieve error value
			mov			[rax], r8		; *errno = error value
			mov			rax, -1			; return = -1
			ret