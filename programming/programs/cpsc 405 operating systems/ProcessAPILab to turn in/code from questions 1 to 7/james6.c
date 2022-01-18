//source: 
//https://www.geeksforgeeks.org/wait-system-call-c/
//https://linux.die.net/man/3/waitpid
//The waitpid() function shall be equivalent to wait() if the pid argument is (pid_t)-1 and the options argument is 0. Otherwise, its behavior shall be modified by the values of the pid and options arguments.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int arc, char *argv[]) 
{

	//print initial values
	printf("At the beginning of main.\n");
	printf("The process at the beginning of main: %i. \n", getpid());

	int status;
	int childpid;
	int process = fork();

	if (process == 0) //if process returned from fork is 0, it is the child
	{

		//wait(NULL);
		printf("This process is the child: %i. \n", getpid());
		
		
	} else //if process returned from fork is a number, it is the pid of the parent 
	{

		childpid = waitpid(process, &status, 0);

		printf("Waiting for the child process to finish.\n");
		printf("This process is the parent: %i. \n", getpid());
		
		if (childpid != -1){
			printf("Child with pid %i sucessfully finished.\n", childpid);	
		} 
		else
		{
			printf("Child not finished.\n");	
		}

	}

	//print end values
	printf("At the end of main.\n");
	printf("The process at the end of main: %i. \n", getpid());

return 0;

}