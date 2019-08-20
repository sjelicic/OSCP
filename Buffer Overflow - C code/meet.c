//meet.c
#include <stdio.h>
#include <string.h>

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

//ova funkcija prima dva argumenta
int greeting(char *temp1, char *temp2) {
	char name[400]; //string variable to hold the name

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

	strcpy(name, temp2); //copy argument(temp2) to name
	printf("Hello %s %s\n", temp1, name); //print out the greeting 
}

int main(int argc, char * argv[]) { //primamo argumente sa komandne linije
	greeting(argv[1], argv[2]); //call function, pass title and name
	printf("Bye %s %s\n", argv[1], argv[2]);
}


/*main()
should be
int main()
the default return type is assumed to be int, that's why it works.*/

/*/home/kangus7/pCloudDrive/OSCP/HTB/meet.c:23:1: 
warning: return type defaults to ‘int’ [-Wimplicit-int]
 greeting(char *temp1, char *temp2) {
 ^~~~~~~~
/home/kangus7/pCloudDrive/OSCP/HTB/meet.c:47:1: 
warning: return type defaults to ‘int’ [-Wimplicit-int]
 main(int argc, char * argv[]) { //primamo argumente sa komandne linije
 ^~~~*/


//rezultat

//nije dat argument
/*kangus7@kali:~$ ./meet 
Hello (null) SHELL=/bin/bash
Bye (null) SHELL=/bin/bash*/

//dva argumenta kako program zahteva
/*kangus7@kali:~$ ./meet Mr Haxor
Hello Mr Haxor
Bye Mr Haxor*/

//tri argumenta
/*kangus7@kali:~$ ./meet Honk Honkler Killy
Hello Honk Honkler
Bye Honk Honkler*/





