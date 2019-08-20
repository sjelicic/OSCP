#include <stdlib.h>
#include <string.h>

//globalne promenljive
//The .data section is used to store global initialized variables

//The below stack section (.bss) is used to store 
//certain types of global uninitialized variables

//The heap section is used to store dynamically 
//allocated variables and grows from the lower-addressed memory 
//to the higher-addressed memory.

//Stack Section
//The stack section is used to keep track of function calls (recursively) 
//and grows from the higher-addressed memory to the lower-addressed memory 
//on most systems. If the process is multithreaded, each thread will have a 
//unique stack. 
//Local variables exist in the stack section.

int _index = 5; //pohranjeno u .data sekciji
char * str; //pointer na str promenljivu tipa char
			//pohranjeno u .bss sekciji 
			//(ne incijalizovana globalna promenljiva)
int nothing; //pohranjeno u .bss sekciji

void function1(int c) {
	int i = c; //pohranjeno u stack sekciju, lokalna promenljiva

/*	“malloc” or “memory allocation” method is used to dynamically 
	allocate a single large block of memory with the specified size. 
	It returns a pointer of type void which can be cast into 
	a pointer of any form.*/

/*	Syntax:
	ptr = (cast-type*) malloc(byte-size)*/


	str = (char*) malloc (10 * sizeof (char)); //reserves 10 characters 
											   //in the heap region

/*	strncpy() function

	The strncpy() function is similar to strcpy() function, 
	except that at most n bytes of src are copied. 
	If there is no NULL character among the first n character of src, 
	the string placed in dest will not be NULL-terminated. 
	If the length of src is less than n, strncpy() writes additional 
	NULL character to dest to ensure that a total of n character are written.*/

/*	Syntax:
	char *strncpy( char *dest, const char *src, size_t n )

	Parameters: This function accepts two parameters as mentioned 
	above and described below:

	src: The string which will be copied.
	dest: Pointer to the destination array where the content is to be copied.
	n: The first n character copied from src to dest.
	Return Value: It returns a pointer to the destination string.*/


	strncpy(str, "abcde", 5); //copies 5 characters "abcde" into str
}

void main() {
	function1(1);
}
