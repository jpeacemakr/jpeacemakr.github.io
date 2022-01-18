//source: https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input

/*
Write a program that connects a child process and a parent process with two pipes. 
Parent process
a.	reads string from terminal prior to fork
b.	writes string read from terminal to first pipe
c.	reads from second pipe
d.	writes what is read from second pipe to terminal
Child process 
e.	reads from first pipe
f.	concatenates fixed_str to what was read
g.	writes concatenated string to second pipe
h.	closes pipes
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main (int arc, char *argv[]) 
{

	//process ids
	//pid_t parent_pid;
	//pid_t child1_pid;

	//create pipe
	int pipe_fd[2]; // file descriptors [0] for reading [1] for writing
	pipe(pipe_fd); 
	char pipe_buffer1[256]; //first string being passed

	//create pipe 2
	int pipe2_fd[2]; // file descriptors [0] for reading [1] for writing
	pipe(pipe2_fd); 
	char pipe2_buffer1[256]; //first string being passed


	//print initial values
	//printf("The process at the beginning of main: %i. \n", getpid());
	//parent_pid = getpid();

	//read string from the terminal
	char input[256];
   	printf("Enter a string: ");
   	fgets(input, 256, stdin);

   	//remove trailing line break
   	//set character at position of \n to 0 
   	input[strcspn(input, "\n")] = 0;

	//create child 
	//printf("Forking for child 1\n");
	int process = fork();

	if (process == 0) //if process returned from fork is 0, it is the child
	{

		/*
		e.	reads from first pipe
		f.	concatenates fixed_str to what was read
		g.	writes concatenated string to second pipe
		h.	closes pipes
		*/

		//child1_pid = getpid();
		//printf("child (pid:%i) started\n", child1_pid);

		//read from pipe and write to string pipe_buffer1
		read(pipe_fd[0], pipe_buffer1, 256); 

		//printf("pipe_buffer1 (initial string): %s\n", pipe_buffer1);

		//perform concatenation operation on pipe_buffer1
		strcat(pipe_buffer1, "fixed_str");

		//write to pipe
		write(pipe2_fd[1], pipe_buffer1, 256);
		
		//printf("child (pid:%i) finished\n", child1_pid);

		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe2_fd[0]);
		close(pipe2_fd[1]);

	}
	else //if process returned from fork is a number, this is the parent. pid returned is child though 
	{

		/*
		Parent process
		a.	reads string from terminal prior to fork//
		b.	writes string read from terminal to first pipe//
		c.	reads from second pipe
		d.	writes what is read from second pipe to terminal
		*/

		//child1_pid = process;
		//printf("parent (pid:%i) started\n", parent_pid);

		//write to pipe
		write(pipe_fd[1], input, 256);

		//read from pipe and write to string pipe_buffer
		read(pipe2_fd[0], pipe2_buffer1, 256); 

		//printf("pipe2_buffer1 (modified string): %s\n", pipe2_buffer1);
		printf("%s\n", pipe2_buffer1);

		//printf("parent (pid:%i) finished\n", parent_pid);

	}

	//print end values
	//printf("At the end of main.\n");
	//printf("The process at the end of main: %i. \n", getpid());

return 0;

}




