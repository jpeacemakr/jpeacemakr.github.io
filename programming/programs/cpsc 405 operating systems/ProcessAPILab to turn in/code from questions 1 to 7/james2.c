//compile with gcc -Wall james2.c -o james2
//sources for syntax:
//https://www.tutorialspoint.com/cprogramming/c_file_io.htm
//https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
//https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  

int main (int arc, char *argv[]) 
{

	//create and open file for writing	
	//FILE *filetowrite;
	//filetowrite = fopen("james2output.txt", "w");

	//int open (const char* Path, int flags [, int mode ]);
	int filenumber = open ("james2output.txt", O_RDWR | O_CREAT); //open file for read and write
    printf("The filenumber is %d\n", filenumber); 

	//print initial values to screen
	printf("At the beginning of main.\n");
	printf("The process at the beginning of main: %i. \n", getpid());
	
	//print initial values to file
	//fprintf(filetowrite, "The process at the beginning of main: %i. ", getpid());
	write(filenumber, "At the beginning of main.\n", strlen("At the beginning of main.\n"));
	
	char pidstring[256]; //is there a way to do this without declaring a string size first?
	sprintf(pidstring, "The process at the beginning of main: %i\n", getpid());
	write(filenumber, pidstring, strlen(pidstring));
	


	//fork it!
	int process = fork();

	if (process == 0) //if process returned from fork is 0, it is the child
	{

		printf("This process is the child: %i. \n", getpid());
		//fprintf(fp, "This process is the child: %i. ", getpid());
		//can also use fputs() put fprintf allows formatting variables		
		sprintf(pidstring, "This process is the child: %i\n", getpid());
		write(filenumber, pidstring, strlen(pidstring));

	} else //if process returned from fork is a number, it is the pid of the parent 
	{

		printf("This process is the parent: %i. \n", getpid());
		//fprintf(fp, "This process is the parent: %i. ", getpid());
		sprintf(pidstring, "This process is the parent: %i\n", getpid());
		write(filenumber, pidstring, strlen(pidstring));
		
	}

	//print end values
	printf("At the end of main.\n");
	printf("The process at the end of main: %i. \n", getpid());
	//fprintf(fp, "This process is the parent: %i. ", getpid());

	sprintf(pidstring, "The process at the end of main: %i\n", getpid());
	write(filenumber, pidstring, strlen(pidstring));
		
	//fclose( filetowrite );
	close(filenumber);

return 0;

}