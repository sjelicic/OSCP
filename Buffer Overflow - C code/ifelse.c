#include <stdio.h>

int main(void){
	int x = 0;
	//while loop uvek tacan
	while (1) {
		//ako je x=0, stampa x=o
		if (x == 0) {
			printf("x = %d\n", x);
			x++; //inkrementira x
			continue;
		}
		//ako x nije jedanko 1, a nece biti u sledecem loop-u
		//stampa x !=0
		else {
			printf("x != 0\n");
			break;
		}
		return 0;
	}
}