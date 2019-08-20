section .data		; section declaration
; ne mogu naci sintaksu za msg (jebem ti sve)

;In assembler there are two "keywords" of sorts to remember: DB and DW. 
;DB tells the compiler to allocate a byte space (8 bits) for a variable, 
;while DW allocates two bytes (16 bits) for the variable. 
;Characters and small numbers are allocated with db while most numbers 
;for arithmetic are dw.

;Line Feed - \n, 0xA, ASCII character 10
;Carriage Return - \r, 0xD, ASCII character 13

msg db "Hello, haxor!",0xa ; ovo nije carriage return jebo vam mater

;How to print the length of a string in assembly
;https://stackoverflow.com/questions/45367779/how-to-print-the-length-of-a-string-in-assembly

;This defines constant len visible during compile time. 
;It doesn't define any memory content, 
;so you can't find it in the executable or during runtime

;The definition is $ - msg, the $ in this context works as "current address", 
;where the next defined machine code byte will be compiled

len equ $ - msg ; length of our string, $ means here

section .text

;A label is not explicitly global until you declare it to be global so you have to use the global directive.
;The global label "_start" is needed by the linker, if there is no global _start address then the linker will complain because it cant find one. You didnt declare _start as a global so it is not visible outside that module/object of code so not visible to the linker.

global _start ;exports the entry point to the ELF linker or loaders 
				; conventioanlly recognize _start as their entry point

_start:
;writing the string (msg) to stdout
;NASM sintaksa
;edx - general register

;The mov instruction copies the data item referred to by its first operand 
;(i.e. register contents, memory contents, or a constant value) 
;into the location referred to by its second operand (i.e. a register or memory).
;While register-to-register moves are possible, direct memory-to-memory moves 
;are not. In cases where memory transfers are desired, 
;the source memory contents must first be loaded into a register, 
;then can be stored to the destination memory address.

mov edx, len ;message length
mov ecx, msg ; pointer to the message to write
mov ebx, 1 ;load first argument (file handle(stdout))
mov eax, 4 ; system call number (4 = sys_write)

;int means interrupt, and the number 0x80 is the interrupt number. An interrupt transfers the program flow to whomever is handling that interrupt, which is interrupt 0x80 in this case. In Linux, 0x80 interrupt handler is the kernel, and is used to make system calls to the kernel by other programs.

;What does “int 0x80” mean in assembly code?\
;https://stackoverflow.com/questions/1817577/what-does-int-0x80-mean-in-assembly-code

int 0x80 ; call kernel interupt and exit

;Linux System Call Table
;https://www.informatik.htw-dresden.de/~beck/ASM/syscall_list.html
;ili
;http://lsi.vc.ehu.es/pablogn/docencia/ISO/2%20Llamadas%20al%20Sistema,%20Kernel/System%20Call%20Table.html

;eax=4 je sys_write
;ebx=1 je int (kako smo dosli do stdout tu nemam pojma)

mov ebx, 0 ; load first syscall argument (exit code)
mov eax, 1 ; system call number (1 = sys_exit)

;So by moving the value 0x1 to EAX register and calling the INT 0x80 in your program, you can make the process go execute the code in Kernel which will stop (exit) the current running process (on Linux, x86 Intel CPU)

int 0x80 ; call kernel interput and exit (eax=1, ebx=0)


