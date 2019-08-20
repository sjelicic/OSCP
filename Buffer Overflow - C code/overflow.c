#include <string.h>
int main() {
	char str1[10];
	strcpy (str1, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
}


/*Kompajler je dovljono inteligentan da primeti buffer overflow
warning: ‘__builtin_memcpy’ writing 54 bytes into a region of size 10 
overflows the destination [-Wstringop-overflow=]*/

//kangus7@kali:~$ ./overflow 
//Segmentation fault
