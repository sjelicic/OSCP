#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	setuid(0);
	system("cat /root/root.txt > /usr/writeup.flag.txt");
	return 0;
}

