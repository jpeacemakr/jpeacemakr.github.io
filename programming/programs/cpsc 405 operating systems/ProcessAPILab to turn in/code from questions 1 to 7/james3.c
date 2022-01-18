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
	
	} else //if process returned from fork is a number, it is the pid of the parent 
	{
		//sleep(1);
		printf("Goodbye\n");

	}

return 0;

}