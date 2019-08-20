/*char code[] = "\xb0\x01\x31\xdb\xcd\x80";
int main(int argc, char **argv)
{
  int (*func)();
  func = (int (*)()) code;
  (int)(*func)();
}*/

char shellcode[] = ""; //global array

/*To pass command line arguments, we typically define main() with two arguments : 
first argument is the number of command line arguments and second is list of 
command-line arguments*/.

//int main(int argc, char *argv[]) { /* ... */ }
//or
//int main(int argc, char **argv) { /* ... */ }

/*argc (ARGument Count) is int and stores number of command-line arguments passed 
by the user including the name of the program. So if we pass a value to a 
program, value of argc would be 2 (one for argument and one for program name)
The value of argc should be non negative.*/

/*argv(ARGument Vector) is array of character pointers listing all the arguments.
If argc is greater than zero,the array elements from argv[0] to argv[argc-1]
will contain pointers to strings.
Argv[0] is the name of the program , After that till argv[argc-1] every element 
is command -line arguments.*/

//** predstavlja double pointer
//https://www.tutorialspoint.com/cprogramming/c_pointers.htm
//https://stackoverflow.com/questions/5580761/why-use-double-indirection-or-why-use-pointers-to-pointers

//https://fresh2refresh.com/c-programming/c-pointer/
/*& symbol is used to get the address of the variable.
* symbol is used to get the value of the variable that 
the pointer is pointing to.*/

/*Reference operator (&) and Dereference operator (*)
As discussed, & is called reference operator. It gives you the address of a 
variable.
Likewise, there is another operator that gets you the value from the address, 
it is called a dereference operator  *.*/

int main (int argc, char **argv) {
	//How to declare a pointer to a function?
	//https://www.geeksforgeeks.org/how-to-declare-a-pointer-to-a-function/

	//How do function pointers in C work?
	//https://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work

	//Double Pointer (Pointer to Pointer) in C
	//https://www.geeksforgeeks.org/double-pointer-pointer-pointer-c/

	// ret pointer to a function which returns int and takes no arguments
	int (*ret)(); //ret is a function pointer
	//cast-ujem shellcode (char) kao pointer ka funkciji koja vraca int
	//Testing Shellcodes
	//https://marcosvalle.github.io/osce/2018/05/03/testing-shellcode.html
	ret = (int(*)())shellcode; //ret points to our shellcode, shellcode is type cast as a function
	ret(); //pozivam ret

	retunrn 0;
}