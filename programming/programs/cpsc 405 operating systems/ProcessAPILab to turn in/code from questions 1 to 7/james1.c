//compile with gcc -Wall james1.c -o james1


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int arc, char *argv[]) 
{

	int x = 100;

	//print initial values
	printf("At the beginning of main.\n");
	printf("The process at the beginning of main: %i. ", getpid());
	printf("x = %i\n", x);


	int process = fork();

	if (process == 0) //if process returned from fork is 0, it is the child
	{

		printf("This process is the child: %i. ", getpid());
		x = x + 100;
		printf("x after adding 100 = %i\n", x);

	} else //if process returned from fork is a number, it is the pid of the parent 
	{

		printf("This process is the parent: %i. ", getpid());
		x = x + 200;
		printf("x after adding 200 = %i\n", x);

	}

	//print end values
	printf("At the end of main.\n");
	printf("The process at the end of main: %i. ", getpid());
	printf("x = %i\n", x);

return 0;

}