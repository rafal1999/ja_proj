CPU x64
DEFAULT REL 



SECTION .data
height: dd  10
width:  dd  10
scale:   dq  2 
byteWidh: dq 0
SECTION .text

global convert
global srednia_xmm




	; al zajęty 
; rdi pImage 
; rsi wsk na wsk 
; rbx *tabVal wsk na wiersz
; rdx height zajęte przez pętle 
; rcx width zajęte przez pętle 
; r9 scale na rzie to jest pomoc do bytewuith *y 
;	r8 bytewidth 
; r10 n ale tymacz pomocnicze przy liczeniu adresu    
; r11 m
;	r12 n
convert:
	mov [byteWidh],r8
	mov r8,rdx
	
	xor rdx,rdx
	mov rdx,[rsp+8]
	push	rsi
	push rbx
	push r12
	xor rax,rax
	mov [width],ecx
	mov [scale],r9
	xor rcx,rcx
row:
	xor rcx,rcx
	mov rax,[byteWidh]; w rax byteWidh
	push rdx ; to jest y
	mul rdx ;mul trzba uważać bo wynik jest współdzielony z rdx  
	mov r9 ,rax ; w r9 bytewidth * y 
	xor rax,rax 
	pop rdx ; przywracanie po mnozeniu 
	mov rax,rdx ;y do rax 	
	push rdx 
	xor rdx,rdx
	div qword [scale] ;y/scale 
	mov r11,rax
	mov rbx, [rsi+(r11*8)]; w rbx adres wiersza
	pop rdx 
	col:
		mov rax,rcx ; x do rax 
		push rdx ; zapisanie rdx na stos bo współdzieli przy mnożeniu z rax 
		xor rdx,rdx
		div qword [scale]  ; y/scale 
		mov r12,rax ; w r12 jest n=x/scale 
		xor rdx,rdx
		mov rax,rcx
		mov rdx , 3  
		mul rdx	; 3 * x
		pop rdx
		xor r10,r10	
		mov r10,rax ;  3*x 
		add r10,r9 ; (3*x)+(_byteWidth*y)
		xor rax, rax 
		mov al, byte [rdi+r10]; w al jeden bajt
		add DWORD  [rbx+(r12*4)] , eax
		mov al, byte [rdi+r10+1] ; 
		add DWORD	 [rbx+(r12*4)] , eax
		mov al, byte [rdi +r10 +2]
		add DWORD	 [rbx+(r12*4)] , eax ; dodanie bajtu
		;add rbx, 4 ; o 4 bajty tyle ile ma int 
		; add rdi, 3 ; przesuniecie na kojnego piksela o (czyli o 3 bajty )
		inc rcx
		cmp ecx,[width]
		jne col 
	; pop rcx ; włozenie do rcx początkowej wartości wierszy 
	; add rsi, 8 ;na kolejny wiersz tablicy przesuniecie 
	inc  rdx ;inkrementacja 
	cmp edx,r8d
	jne row
	pop r12 
	pop rbx
	pop rsi
	ret

		srednia_xmm:
	push rdx
	xor rax,rax
	xor rdx,rdx
	mov rax,3 ; 3*scale*scale 
	mul rcx   ;
	mul rcx   ;
	cvtsi2ss xmm1, rax ; 
	xor r9,r9
	shufps xmm1,xmm1, 0h
	mov r9, 4
	xor rax,rax
	mov rax,8; liczy pierwszy adres wersza 
	mul r8;
	sub rsi, r8
	add rdi,rax;
	pop rdx
	xor rax,rax
	mov rax, rdx
	xor rdx,rdx
	div r9
	r:
		mov r9, [rdi]
		push rdx
		push rax
	c:
		cvtdq2ps xmm0, [r9] ; w xmm0 4 komórki 
		divps xmm0,xmm1
		cvtps2dq xmm0,xmm0
		movaps  [r9],xmm0
		add r9, 4*4
		dec rax
		cmp rax,0
		jne c
		cmp rdx,0
		je rc
		e1:
		cvtsi2ss xmm0,[r9]
		xor r11,r11
		divps xmm0,xmm1
		cvtss2si r11,xmm0
		mov DWORD [r9], r11d
		dec rdx
		add r9, 4 ; o 1 int presówam 
		cmp rdx,0
		jne e1
		rc:
		cmp rsi,0
		pop rax
		pop rdx
		je end
		dec rsi
		add rdi,8 ; na koleny wiersz 
		cmp rsi,0
		jne r
		end:
		ret