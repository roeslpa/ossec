section .data

szEnter: db "Enter three numbers:", 0
szScan:  db "%d %d %d", 0

szResult: db "Result: %d+%d-%d=%d", 0xa, 0

;; Paul Rösler 108012225686 Ue1.1
;; might be interesting:
;; reserve, say 4096 bytes 
;; comment the bss section
;; assemble and check size of obj file
;; uncomment bss section
;; assemble and check size of obj file
section .bss

n1: resb 4
n2: resb 4
n3: resb 4
res: resb 4

section .text 

global start
extern printf, scanf


start:

    push szEnter
    call printf
    add esp, 4
    
;;int scanf ( const char * format, ... );
    push n3
	push n2
    push n1
    push szScan
    call scanf
    add esp, 16

    mov eax, [n1]
    mov ebx, [n2]
    add eax, ebx
	mov ebx, [n3]
	sub eax, ebx
    mov [res], eax
   
    push dword [res]
	push dword [n3]
    push dword [n2]
    push dword [n1]
    push szResult
    call printf
    add esp, 20

    ret
    
    
    
    
