#include <string.h>
#include <stdio.h>

void overflowed() {
	printf("%s\n", "Execution hijacked");
}

/*Pointers in C language is a variable that 
stores/points the address of another variable. 
A Pointer in C is used to allocate memory dynamically i.e. at run time. 
The pointer variable might be belonging to any of the data type 
such as int, float, char, double, short etc.*/

/*Pointer Syntax : 
data_type *var_name; 
Example : 
int *p;  char *p;
Where, * is used to denote that “p” is pointer variable 
and not a normal variable.*/

/*& symbol is used to get the address of the variable.
* symbol is used to get the value of the variable that 
the pointer is pointing to.*/

void function1(char *str) {
	char buffer[5];

/*	strcpy() is a standard library function in C/C++ 
	and is used to copy one string to another. 
	In C it is present in string.h header file 
	and in C++ it is present in cstring header file.*/

/*	Syntax:
	char* strcpy(char* dest, const char* src);

	Paramters: This method accepts following paramters:
	dest: Pointer to the destination array where the content 
		  is to be copied.
	src: string which will be copied.*/

/*	Return Value: After copying the source string to the 
				  destination string, the strcpy() function 
				  returns a pointer to the destination string.*/


	strcpy(buffer, str);
}

/*Syntax:
int main(int argc, char *argv[])

Here argc counts the number of arguments on the command line and argv[ ] is a pointer array which holds pointers of type char which points to the arguments passed to the program.

argc integer holds the number of arguments and the argv array holds the input arguments (strings)
The name of the program is always stored at offset argv[0]*/

void main(int argc, char *argv[]) {
	//prima prvi argument sa komande linije
	function1(argv[1]); 		
	printf("%s\n", "Executed normally" ); 
}
