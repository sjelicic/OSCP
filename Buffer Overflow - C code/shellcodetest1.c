//Grayhat Hacking primer
/*char code[] = "\x31\xc0\xb0\x01\x31\xdb\xcd\x80";
int main(int argc, char **argv)
{
  int (*func)();
  func = (int (*)()) code;
  (int)(*func)();
}*/

char shellcode[] = "\x31\xc0\xb0\x01\x31\xdb\xcd\x80";             /* global array */
int
main (int argc, char **argv)
{
        int (*ret)();              /* ret is a function pointer */
        ret = (int(*)())shellcode; /* ret points to our shellcode */
                                   /* shellcode is type caste as a function */
        (int)(*ret)();             /* execute, as a function, shellcode[] */
        //exit(0);                   /* exit() */
}