CPU x64

extern printf


SECTION .data
msg: db "Daj kamienia!",0
formats: db "%s", 10, 0


SECTION .text
global m

m:
	push rbp
	mov rdi, formats 
	mov rsi, msg
	xor rax, rax
	call printf 

	pop rbp
	xor eax, eax
	ret
