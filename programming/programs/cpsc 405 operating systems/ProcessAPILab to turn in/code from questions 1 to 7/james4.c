//compile with gcc -Wall james1.c -o james1
//sources:
//https://www.geeksforgeeks.org/exec-family-of-functions-in-c/

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

		printf("This process is the child: %i. \n", getpid());
		
		printf("Child running the exec command\n");

		//int execvp (const char *file, char *const argv[]);
		//char *args[]={"ls", NULL}; 
        //execvp(args[0],args); 
		
		execlp("ls", "ls", NULL);

		printf("\n");

	} else //if process returned from fork is a number, it is the pid of the parent 
	{

		printf("This process is the parent: %i. \n", getpid());
		printf("Parent running without the exec command\n");
		
	}

	//print end values
	printf("At the end of main.\n");
	printf("The process at the end of main: %i. \n", getpid());

return 0;

}