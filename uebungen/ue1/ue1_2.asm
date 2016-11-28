section .data

szEnter1: db "Which operation? + (0), - (1), * (2):", 0
szScan1:  db "%d", 0
szEnter2: db "Two numbers for the operation:", 0
szScan2:  db "%d %d", 0
szFalse: db "Not an option!", 0

szResult: db "Result: %do%d=%d", 0xa, 0

;; Paul Rösler 108012225686 Ue1.2
;; might be interesting:
;; reserve, say 4096 bytes 
;; comment the bss section
;; assemble and check size of obj file
;; uncomment bss section
;; assemble and check size of obj file
section .bss

x: resb 4
a: resb 4
b: resb 4
res: resb 4

section .text 

global start
extern printf, scanf


start:

    push szEnter1
    call printf
    add esp, 4
    
;;int scanf ( const char * format, ... );
    push x
    push szScan1
    call scanf
    add esp, 8

	mov eax, [x]
	sub eax, 3
	JNS false
	
	push szEnter2
    call printf
    add esp, 4
	
	push b
	push a
    push szScan2
    call scanf
    add esp, 12
	
    mov eax, [a]
    mov ebx, [b]

	mov edx, [x]
	dec edx
	JS addi
	dec edx
	JS subs
	
mult:
	mul ebx
	JMP result
subs:
	sub eax, ebx
	JMP result
addi:
	add eax, ebx
    
result:
	mov [res], eax
   
    push dword [res]
    push dword [b]
    push dword [a]
    push szResult
    call printf
    add esp, 16

    ret
    
false:
	push szFalse
    call printf
    add esp, 4
    ret
    
