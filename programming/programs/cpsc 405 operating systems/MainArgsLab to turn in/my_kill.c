/* James Peacemaker, Feb 7, 2021, CPSC 405
I used the following websites as a reference for syntax or to learn how some things worked. I did not copy code from them.
https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html
https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
https://www.tutorialspoint.com/cprogramming/c_file_io.htm
https://www.geeksforgeeks.org/getppid-getpid-linux/
https://man7.org/linux/man-pages/man2/kill.2.html
https://www.tutorialspoint.com/c_standard_library/errorno_h.htm
https://www.studymite.com/blog/strings-in-c#read_using_getline
*/

/*
Write a program - my_kill.c - where main processes two options (arguments with a -) and one
argument. The two options are the following.
● -h - When this option is present my_kill prints Hello World to the terminal.
● -f file -When this option is present, my_kill prints the contents of the file to the
terminal. You can assume that file is a text file.
● The argument that is not an option is a process id.
Your program is executed via the following.
./my_kill -h -f tiny.txt 1234
./my_kill 1234
./my_kill -h 1234
./my_kill -ftinytxt 1234
● -h - this informs my_kill to print Hello World to the terminal.
● -f tiny.txt - this informs my_kill to print the contents of tiny.txt to the terminal.
● 1234 is a process id.
● You can use either command options take one or take two for processing your options. I
used command options take two.
● Your program shall terminate with a -1 if it is invoked without a process id to terminate.
You will have to determine this. If you use command options take two, getopt has a
global variable optind that can be used.
if ((argc - optind) != 1) {
printf("Error - command format is $ my_kill -options pid\n");
exit(-1);
}
● Your program shall print its process id to standard output.
printf("my_kill pid: %d\n", getpid()); // get my_kill’s pid
● Your program shall call kill sending a SIGINT signal to the process id passed as an
argument to my_kill . Include the following lines of code in your program.
int status = kill(pid_to_kill, SIGINT);
int errnum = errno;
if (status == -1) {
fprintf(stderr, "Value of errno: %d\n", errno);
perror("Error printed by perror");
fprintf(stderr, "Error killing process: %s\n", strerror( errnum
));
6
}
● Your program shall return 0 for normal completion.

*/

#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h> 
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FN_LEN 256

struct Options {
    bool using_h; // -h, print hello world if true
    bool using_f; // -f, print text of file if true
    int pid; // process id of process to kill
    char filename[FN_LEN]; // -f optarg
};



//initializes opts
static void init_opts(struct Options* opts) {
    
    //printf("DEBUG: starting init_opts\n");

    opts->using_h = false;
    opts->using_f = false;
    opts->pid = -1;
    for (int i = 0; i < FN_LEN; i++)
        opts->filename[i] = 0;
}


//gets the options and returns the structure
struct Options get_opts(int count, char* args[]) {
    
    //printf("DEBUG: starting get_opts\n");

    struct Options opts; //stores the options
    init_opts(&opts); //initializes opts. values get false, etc.
    int opt; //used to hold the output of getopt()

    while ((opt = getopt(count, args, ":f:h")) != -1) {
        switch (opt) {
            case 'h': opts.using_h = true; break;
            case 'f': 
                opts.using_f = true; 
                strcpy(opts.filename, optarg); 
                break;
            case ':': 
                printf("-f needs a value\n");
                break;
            case '?': 
                printf("Unknown option\n");
                break;
        }
    }
    //printf("DEBUG: last args %s\n", args[count-1]);
    
    //check to see if last argument is an integer. if so, set pid to it
    //needed to add an or for "0" since atoi returns 0 if failed or string is "0"
    if (atoi(args[count-1]) || (strcmp (args[count-1], "0") == 0))
    {
        //printf("DEBUG: last args is an integer %s\n", args[count-1]);
        opts.pid = atoi(args[count-1]);
    }

    return opts;
}



//prints the contents of the input file to the screen
void print_file(char* filename)
{

    //printf("DEBUG: starting print_file\n");

    //set input file    
    //printf("DEBUG: print_file 1\n");
    FILE *input;

    //printf("DEBUG: print_file 2\n");
    //printf("DEBUG: %s\n", filename);
    input = fopen(filename, "r");
    
    //if file can't be opened, print error message and exit with failure code
    if (input == NULL) {
        printf("Error opening file %s\n", filename);
        exit(-1);
    }

    printf("Printing file %s\n", filename);


    //read lines from file and print them. but is limited to tempstring size.
    //I redid this section below using getline()
    /*
    printf("DEBUG: print_file 3\n");
    char tempstring[256]; //string used to bring in each line

    printf("DEBUG: print_file 4\n");
    while (fgets( tempstring, 256, input) ){
        printf("%s", tempstring); 
    } 
    */

    //read lines from file and print them. 
    //printf("DEBUG: print_file 3\n");

    //int tempstringsize = 1; //this gave a warning
    size_t tempstringsize = 1;
    
    char *tempstring; //string used to bring in each line
    tempstring = (char *) malloc (tempstringsize);

    //printf("DEBUG: print_file 4\n");
    while ( getline(&tempstring, &tempstringsize, input) != -1 ){
        printf("%s", tempstring); 
    } 

    //close file
    fclose(input);
}


//kills the process with the corresponding id
int kill_pid(int pid_to_kill)
{

    //printf("DEBUG: Killing process pid: %i\n", pid_to_kill);

    int status = kill(pid_to_kill, SIGINT);
    int errnum = errno;
    
    if (status == -1) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error killing process: %s\n", strerror( errnum));
        return -1;
    }
    return 0;
}




int main(int argc, char *argv[]) {
    
    //printf("DEBUG: starting main\n");

    struct Options o = get_opts(argc, argv);
    int success;

    if (o.using_h) 
    {
        printf("Hello world\n");
    }    
    if (o.using_f) 
    {
        print_file(o.filename);
    }


    //if pid to kill exists, kill it. Else print error
    if (o.pid!=-1)
    {
        //print the process id of this program    
        printf("my_kill pid: %d\n", getpid()); // get my_kill’s pid

        //success = 0 if found. -1 if not found. returned by main to show successful run.
        success = kill_pid(o.pid);
    } 
    else
    {
        printf("Error - command format is $ my_kill -options pid\n");
        exit(-1);
    }

    return success;

}