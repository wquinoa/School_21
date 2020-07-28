;ssize_t read(int fildes, void *buf, size_t nbyte);
;int rdi = fd;
;char* rsi = buf;
;int rdx = nbyte;

section .text
	global _ft_read
	extern ___error

_ft_read:
			mov			rax, 0x2000003	; call read
			syscall
			jc			_read_err		; if (syscall != 0) goto read_err
			ret							; else return
_read_err:
			push		rax				; save value returned by syscall
			call		___error		; call error. rax = &errno
			pop			r8				; retrieve error value
			mov			[rax], r8		; *errno = error value
			mov			rax, -1			; return = -1
			ret