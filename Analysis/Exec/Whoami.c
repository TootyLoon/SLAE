// msfvenom -p linux/x86/exec cmd=whoami -f c

unsigned char buf[] = 
"\x6a\xBF\x58\x99\x52\x66\x68\x2d\x63\x89\xe7\x68\x2f\x73\x68"
"\x00\x68\x2f\x62\x69\x6e\x89\xe3\x52\xe8\x07\x00\x00\x00\x77"
"\x68\x6f\x61\x6d\x69\x00\x57\x53\x89\xe1\xcd\x80";



/*
push   0xb        ;preparing execve syscall {execve (%ebx , %ecx, %edx)}
pop    eax
cdq               ;clears edx
push   edx				;pushes 0
pushw  0x632d			;pushes 2 bytes for execve argument [-c]
mov    edi,esp		;put [-c] to edi

push   0x68732f		;pushes [/bin/sh]
push   0x6e69622f
mov    ebx,esp		;put [/bin/sh] to ebx

push   edx				;pushes 0
call   0xbfffef49
ja     0xbfffefac	;the next set of instructions represent [whoami] 
outs   dx,DWORD PTR ds:[esi]
popa   
ins    DWORD PTR es:[edi],dx

0xbfffef49:	push   edi	;contains [-c]
push   ebx				      ;contains [/bin/sh]
mov    ecx,esp			    ;[/bin/sh -c whoami] final representation of the argument of execve
int    0x80				      ;execve
*/
