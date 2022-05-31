GLOBAL cpuVendor
GLOBAL keyPress
GLOBAL keyboardStatus

section .text
	

keyboardStatus:
	mov rax, 0
    in al, 64h
    and al, 01h 
    ret


keyPress:
	mov rax, 0
    in al, 60h
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
