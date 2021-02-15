CPU x64
DEFAULT REL 

SECTION .data
test: dd 3F80H ;zakraglanie do -inf

SECTION .text

global convert_asm
global average_asm





; rdi pImage - wskaźnik na tablice RGBRGBRGB...
; rsi tabValues - tablica wartości (2D wsk na wsk)
; rdx bytewidth - szerokość wiersza w poj. wartościach RGB
; rcx width - szerokość obrazka   (długość jednego wiersza) 
;	r8 - do której komórki (pImage) jest wykonywane przetwarzanie 
; r9 scale - skala
; 7 argument na stosie - od której komórki (pImage) jest rozpoczęte przetwarzanie

convert_asm:
	mov r10,rdx  											 ;w r10 bytewidth
	xor rdx,rdx
	mov rdx,[rsp+8]
	push rbx
	xor rax,rax
	push r12
	push r10	
row:
	pop r10
	push rdx ; y
	mov rax,r10													;w rax byteWidh
	mul rdx															;byteWidth * y 
	mov r11 ,rax 												;w r11 bytewidth * y 
	pop rdx ; y
	xor rax,rax 
	push r10
	mov rax,rdx 												;y do rax 	
	push r11
	push rdx 														;y
	xor rdx,rdx
	div r9 															;y/scale 
	pop rdx
	mov r11,rax 												;w r11 y/scale 
	mov rbx, [rsi+(r11*8)] 							;w rbx adres wiersza tabVal
	pop r11
	push r8															; wrzucenie na stos wysokości obrazka
	mov r8, rcx													;w r8 szerokość obrazka
	xor rcx,rcx
col:
	push rdx		
	mov rax,rcx 												;x do rax 											
	xor rdx,rdx
	div r9					  									;x/scale 
	mov r12,rax 												;w r12 jest n=x/scale 
	xor rdx,rdx
	mov rax,rcx
	mov rdx , 3  
	xor r10,r10	
	mul rdx															;3 * x
	pop rdx
	mov r10,rax 												;w r10  3*x 
	xor rax, rax 
	add r10,r11 												;(3*x)+(_byteWidth*y)
	mov al, byte [rdi+r10]							;w al jeden bajt pImage
	add DWORD  [rbx+(r12*4)] , eax
	mov al, byte [rdi+r10+1] 
	add DWORD	 [rbx+(r12*4)] , eax
	mov al, byte [rdi +r10 +2]
	add DWORD	 [rbx+(r12*4)] , eax 
	inc rcx
	cmp rcx,r8
	jne col 
	pop r8 															   															
	inc  rdx 														
	cmp rdx,r8
	jne row
	pop r12 
	pop rbx
	pop r10
	ret

;rdi **tabValues - tablica wartości 
;rsi numer ostatniego wiersza który będze przetwarzany  
;rdx widthTabVal - szerokośc tablicy wartości 
;rcx scale - skala 
;r8 numer od którego algorytm rozpoczyna przedtwarzanie 
average_asm:
	push rdx 							;zapisanie wartości przed mnożeniem i dzieleniem 
	xor rax,rax
	xor rdx,rdx
	mov rax,3 						; 3*scale*scale 
	mul rcx   						;
	mul rcx   						;
	cvtsi2ss xmm1, rax 		;w xmm1  3*scale*scale (w 1 komórce v4_int32)
	xor r9,r9
	shufps xmm1,xmm1, 0h	;w v4_int32 są wartość 3*scale*scale
	mov r9, 4 						;w r9 ile danych będzie przetwarzanych równocześnie 
 	xor rax,rax
	mov rax,8							;liczy pierwszy adres wersza 
	mul r8;
	sub rsi, r8						;w rsi liczba iteracji 
	add rdi,rax 					;przesunięcie adresu na odpowiedni wiersz 
	pop rdx 							;odzyskanie tabValues wartości po wykonaniu dzielenia 
	xor rax,rax
	mov rax, rdx 					;w rax widthTabVal
	xor rdx,rdx
	div r9 								;ile razy można  pobrać 4  dane za jednym razem, 
												;w rdx ile komórek będze trzeba oblczyć pojedynczo 
	xor r9,r9
r: ; row
	mov r9, [rdi] 				;w r9 adres wiersza 
	push rdx
	push rax 							;w rax ile razy mozna pobrać 4 komórki za jednym razem 
c: ;col
	cvtdq2ps xmm0, [r9] 	;w xmm0 4 komórki 
	divps xmm0,xmm1
	cvtps2dq xmm0,xmm0		;konwersja na int 
	movaps  [r9],xmm0 		;załadowanie podzielonych danych 
	add r9, 4*4 					;przejście na kolejne 4 komórki 
	dec rax
	cmp rax,0
	jne c
	cmp rdx,0 
	je rc 					  		;skok jesli nie trzeba rozpatrywać przypadku gdy 
												;liczba komórek jest niepodzielna przez 4
e1: 										;obliczanie ostanich (pozostałych) 3,2, lub 1 komórek/komórki  
	cvtsi2ss xmm0,[r9] 
	xor r11,r11
	divps xmm0,xmm1
	cvtss2si r11,xmm0
	mov DWORD [r9], r11d
	dec rdx
	add r9, 4 					 
	cmp rdx,0
	jne e1
rc:											;gdy nie trzeba rozpatrywać przypadku gdy 
												;liczba  jest niepodzielna przez 4 komórek   
	cmp rsi,0
	pop rax
	pop rdx
	je end
	dec rsi
	add rdi,8 						;przejście  na koleny wiersz 
	cmp rsi,0
	jne r
end:
	ret

	