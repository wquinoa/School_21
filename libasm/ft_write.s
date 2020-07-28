;ssize_t write(int fd, const void *buf, size_t nbyte)
;int rdi = fd;
;char* rsi = buf;
;int rdx = nbyte;

section .text
	global _ft_write
	extern ___error

_ft_write:
			mov			rax, 0x2000004	; call write
			syscall
			jc			_wrerr			; if (syscall != 0)
			ret							; else return
_wrerr:
			push		rax				; save value returned by syscall
			call		___error		; call error. rax = &errno
			pop			r8				; retrieve error value
			mov			[rax], r8		; *errno = error value
			mov			rax, -1			; return = -1
			ret