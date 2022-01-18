//compile with gcc -Wall james1.c -o james1


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int arc, char *argv[]) 
{

	int process = fork();

	if (process == 0) //if process returned from fork is 0, it is the child
	{

		printf("Hello\n");
		printf("Hello\n");
		printf("Hello\n");
		printf("Hello\n");
		printf("Hello\n");
		printf("Hello\n");
		printf("Hello\n");

	} else //if process returned from fork is a number, it is the pid of the parent 
	{

		int num = 1;
		for (int i = 1; i < 10000000; ++i)
		{
			num = num + 13978;
		}

		printf("Goodbye\n");
		printf("Goodbye\n");
		printf("Goodbye\n");
		printf("Goodbye\n");
		printf("Goodbye\n");
		printf("Goodbye\n");
		printf("Goodbye\n");

	}

return 0;

}