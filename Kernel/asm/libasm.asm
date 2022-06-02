GLOBAL cpuVendor
GLOBAL keyPress
GLOBAL keyboardStatus

section .text
	

keyboardStatus:
    push rbp
    mov rbp,rsp
    
    xor rax, rax
    in al,60h

    mov rsp, rbp
	pop rbp
    ret


keyPress:
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
