CPU x64

extern printf


SECTION .data
msg: db "Daj kamienia!",0
formats: db "%s", 10, 0


SECTION .text
global m
global zwroc_double



m:
	push rbp
	mov rdi, formats 
	mov rsi, msg
	xor rax, rax
	call printf 

	pop rbp
	xor eax, eax
	ret

global   maxofthree
maxofthree:
        mov     rax, rdi                ; result (rax) initially holds x
      ; cmp     rax, rsi                ; is x less than y?
       ; cmovl   rax, rsi                ; if so, set result to y
       ; cmp     rax, rdx                ; is max(x,y) less than z?
       ; cmovl   rax, rdx                ; if so, set result to z
        ret    
zwroc_double:
	movsd xmm0 ,[rdi]
	addsd xmm0, [rdi]
	ret
	