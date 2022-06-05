GLOBAL cpuVendor
GLOBAL keyPress
GLOBAL keyboardStatus
GLOBAL getRTC
GLOBAL saveRegisterInfo
GLOBAL getSP

EXTERN savereg

section .text

saveRegisterInfo:

	mov [buffer], rax				
	mov [buffer + 1*8], rbx			
	mov [buffer + 2*8], rcx			
	mov [buffer + 3*8], rdx			
	mov [buffer + 4*8], rsi				
	mov [buffer + 5*8], rdi
	mov [buffer + 6*8], r8
	mov [buffer + 7*8], r9
	mov [buffer + 8*8], r10
	mov [buffer + 9*8], r11
	mov [buffer + 10*8], r12
	mov [buffer + 11*8], r13
	mov [buffer + 12*8], r14
	mov [buffer + 13*8], r15
	mov [buffer + 14*8], rsp
	mov rax, [rsp] 				; RIP.
    mov [buffer + 15*8], rax
	
	mov rdi, buffer
	call savereg

	ret

	

keyPress:
    push rbp
    mov rbp,rsp
    
    xor rax, rax
    in al,60h

    mov rsp, rbp
	pop rbp
    ret


keyboardStatus:
    push rbp
    mov rbp,rsp

    xor rax, rax
    in al,64h
    and al,0x01

    mov rsp, rbp
	pop rbp
    ret

	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


getRTC:
	cli
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al

    mov rax, rdi

    out 70h, al
    in al, 71h
    
    sti
    ret


section .bss
	buffer: resb 128

	