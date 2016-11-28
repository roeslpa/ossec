section .data

szEnter1: db "What's your string?", 0
szScan1:  db "%s", 0

szResult: db "Result: %d", 0xa, 0

;; Paul Rösler 108012225686 Ue1.3
;; might be interesting:
;; reserve, say 4096 bytes 
;; comment the bss section
;; assemble and check size of obj file
;; uncomment bss section
;; assemble and check size of obj file
section .bss

string: resb 4
res: resb 4

section .text 

global start
extern printf, scanf


start:

    push szEnter1
    call printf
    add esp, 4
    
;;int scanf ( const char * format, ... );
    push string
    push szScan1
    call scanf
    add esp, 8
	
	mov ecx, 0

	mov edx, string
	mov eax, [edx]
	
addi:
	mov ebx, eax
	and ebx, 0xFF
	add ecx, ebx
	shr eax, 8
	mov ebx, eax	
	and ebx, 0xFF
	add ecx, ebx
	shr eax, 8
	mov ebx, eax
	and ebx, 0xFF
	add ecx, ebx
	shr eax, 8
	mov ebx, eax
	and ebx, 0xFF
	add ecx, ebx
	
	add edx, 4
	mov eax, [edx]
	cmp eax, 0
	JNZ addi
	
    push ecx
    push szResult
    call printf
    add esp, 8
    ret
