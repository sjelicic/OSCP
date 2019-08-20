#include <stdio.h>

int main(void) {
	int x =0;

	while (x<10) {
		printf("x = %d\n", x);
		x++;
	}
	return 0;
}

/*It is important to note the use of the less-than operator (<) 
in place of the less-than-or-equal-to operator (<=), 
which allows the loop to proceed one more time until i=10. 
This is an important concept that can lead to off-by-one errors. 
Also, note that the count started with 0. 
This is common in C and worth getting used to.*/