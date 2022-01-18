
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int arc, char *argv[]) 
{

	//print initial values
	printf("At the beginning of main.\n");
	printf("The process at the beginning of main: %i. \n", getpid());

	int process = fork();

	if (process == 0) //if process returned from fork is 0, it is the child
	{

		printf("This process is the child before closing standard output: %i. \n", getpid());
		close(STDOUT_FILENO);
		printf("This process is the child after closing standard output: %i. \n", getpid());
		
	}
	else //if process returned from fork is a number, it is the pid of the parent 
	{

		printf("This process is the parent: %i. \n", getpid());
	
	}

	//print end values
	printf("At the end of main.\n");
	printf("The process at the end of main: %i. \n", getpid());

return 0;

}