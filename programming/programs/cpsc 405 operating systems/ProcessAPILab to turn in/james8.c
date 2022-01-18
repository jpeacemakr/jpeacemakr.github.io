//source: 
//https://www.geeksforgeeks.org/pipe-system-call/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main (int arc, char *argv[]) 
{

	//process ids
	pid_t parent_pid;
	pid_t child1_pid;
	pid_t child2_pid;

	//create pipe
	int pipe_fd[2]; // file descriptors [0] for reading [1] for writing
	pipe(pipe_fd); 
	char pipe_buffer1[256]; //first string being passed
	char pipe_buffer2[256]; //second string being passed

	//print initial values
	//printf("At the beginning of main.\n");
	//printf("The process at the beginning of main: %i. \n", getpid());
	parent_pid = getpid();
	printf("Parent of two children connected via pipe. (pid:%i)\n",parent_pid);

	//create child 1. This is the writer child. 
	//it will actually wait until something is put in the pipe?
	//printf("Forking for child 1\n");
	int process = fork();


	if (process == 0) //if process returned from fork is 0, it is the child
	{

		child1_pid = getpid();

		//printf("This process is child 1: %i. \n", child1_pid);
		printf("child 1: pipe writer: (pid:%i)\n", child1_pid);

		//write to pipe
		write(pipe_fd[1], argv[1], 256);
		write(pipe_fd[1], "Cooper", 256);
		close(pipe_fd[1]);
		
		printf("childpid: %i finished\n", child1_pid);

	}
	else //if process returned from fork is a number, it is the pid of the parent 
	{

		child1_pid = process;

		//create child 2. this is the read child.
		//printf("Forking for child 2\n");
		int process2 = fork();

		if (process2 == 0) //if process returned from fork is 0, it is the child
		{

			child2_pid = getpid();

			//printf("This process is child 2: %i. \n", child2_pid);
			printf("child 2: pipe reader: (pid:%i)\n", child2_pid);

			//read from pipe and write to string pipe_buffer
			read(pipe_fd[0], pipe_buffer1, 256); 
			read(pipe_fd[0], pipe_buffer2, 256); 
			close(pipe_fd[0]);

			printf("%s%s", pipe_buffer1, pipe_buffer2);

			//print pipe_buffer1 backwards
			int pipe_buffer1_length = strlen(pipe_buffer1);
			while ( pipe_buffer1_length > 0 )
			{
				printf("%c", pipe_buffer1[pipe_buffer1_length-1]);
				pipe_buffer1_length--;
			}
			printf("\n");

			printf("childpid: %i finished\n", child2_pid);

		}

		else //if process returned from fork is a number, it is the pid of the parent 
		{

			child2_pid = process2;

			wait(NULL);
			wait(NULL);
			printf("parentpid:%i of child1pid:%i and child2pid:%i \n", parent_pid, child1_pid, child2_pid);

		}		
	}

	//print end values
	//printf("At the end of main.\n");
	//printf("The process at the end of main: %i. \n", getpid());

return 0;

}




