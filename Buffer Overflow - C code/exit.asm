;exit.asm
section .text
global _start
_start:
; xor eax, eax sets the contents of the eax to zero
xor eax, eax
;moves 1 to the lower 8 bit of the of the General Purpose Register (GPR) eax
;ne znam da li je isto sa 64bitnim registrima
mov al, 1 ;exit is syscall 1 (system call number (1 = sys_exit))
xor ebx, ebx ;u drugom primeru smo imali mov ebx, 0
			 ; uglavnom eax=1, ebx=0 kada pozovemo 0x80 poziva exit funkciju
int 0x80