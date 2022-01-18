#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define DELIMETERS " \t"            // used by strtok, skips whitespace - spaces and tabs
#define BUFSZ 100                   // max size of input line containing commands
#define CMDWORDS 10                 // max words on command line

static char line[BUFSZ];            // cmd line read into line[]

static char *cmd_words[CMDWORDS];   // words on line pointed to by cmd_words[]. addresses in cmd_words are &line[6] for example
static char *cmd_words_p1[CMDWORDS];  //used for first part of two-part command
static char *cmd_words_p2[CMDWORDS];  //used for second part of two-part command

static int num_words = 0;           // number of words on cmd line
static int num_words_p1 = 0;        // number of words on cmd line for first part of two-part command
static int num_words_p2 = 0;        // number of words on cmd line for second part of two-part command

static int volatile done = 0;
static int volatile sig_triggered = 0; //lets main know not to trigger EOF if this is 1
static int volatile test_wait = 0;
                    

/*
 * signal handler for CTL-C
 * CTL-C does not terminate shell, but it does terminate backgroud procs
 */
void handler (int sig)
{
    if (sig==2) 
    {
        printf("\n");
        printf("Closing active programs.\n");
        //printf("Debug: Handling signal: %i\n", sig);
        sig_triggered = 1; //lets main know not to trigger EOF if this is 1
    }
}



/*
 * Called when execvp() returns, which happens when the cmd does not exist
 * Prints error message and exits - the exit is from the child, not the shell
 */
void cmd_not_found(char *cmd) 
{
    fprintf(stderr, "mysh: cmd not found: %s\n", cmd);
    exit(1);                            // exit() from child, not shell
}



/*
 * Checks to see if cmd is cd, and changes directory
 * Returns 1 if the cmd is cd; otherwise returns 0
 */
int cd_cmd() 
{
    if(line[0] == 'c' && line[1] == 'd' && line[2] == ' ')
    { // Clumsy 
        if(chdir(line+3) < 0) // Chdir has no effect on the parent if run in the child.
            fprintf(stderr, "cannot cd %s\n", line+3);
        return 1;
    }
    return 0;
}






/*
 * Checks to see if cmd is cd, and changes directory
 * Returns 1 if the cmd is cd; otherwise returns 0
 */
int pwd_cmd() 
{
    if(line[0] == 'p' && line[1] == 'w' && line[2] == 'd' && line[3] == '\0')
    {  
        char directory_path[256]; //full path of cwd
        getcwd(directory_path, 256);
        printf("directory: %s\n", directory_path);
        return 1;
    }
    return 0;
}



/*
 * Separates line into words on line
 * For each word on line, cmd_words[] points to the word.
 * num_words assigned the number of words on the line
 * returns 0 for line without command
 */
int get_cmd_words() 
{
    // Collect words on line into cmd_words
    num_words = 0;
    char *p;
    p = strtok(line, DELIMETERS);               // strtok() returns pointer to word on line

    while (p != NULL) 
    {                         // p has address in line, e.g., &line[0]
        cmd_words[num_words] = p;               // cmd_words[] points to words on line
        num_words++;                            // count words on line
        p = strtok(NULL, DELIMETERS);           // get next word on line
    }

    cmd_words[num_words] = NULL;                // 0 marks end of words in cmd_words
    return num_words;                           // return num of words found
}



//checks to see if > < or | is in command words
int check_cmd_words(char *check)
{
    //printf("Debug: starting check_cmd_words.\n");

    for (int i=0; i<num_words; i++)
    {
        if (strcmp(cmd_words[i], check) == 0)
        { 
            //printf("Debug: string %s found.\n", check);
            return 1; 
        }
    }
    //printf("Debug: string %s not found.\n", check);
    return 0;
}


//splits cmd_words into two command words cmd_words_p1 and _p2 if < > or | is present
void split_cmd_words()
{
    //printf("Debug: starting split_cmd_words.\n");
    num_words_p1 = 0;
    num_words_p2 = 0;

    //copy cmd_words into cmd_words_p1 until symbol reached
    for (int i = 0; i<num_words; i++)
    {
        if ((strcmp(cmd_words[i], "<") == 0) || (strcmp(cmd_words[i], ">") == 0) || (strcmp(cmd_words[i], "|") == 0))
        { 
            //printf("Debug: <, > or | found.\n");
            num_words_p1 = i;
            break;
        } else 
        {
            //printf("Debug: copying command word %s to cw1.\n", cmd_words[i]);
            cmd_words_p1[i] = cmd_words[i];
        }
    }
    cmd_words_p1[num_words_p1] = NULL;                // 0 marks end of words in cmd_words

    //printf("Debug: num_words_p1: %i.\n", num_words_p1);

    //copy rest of cmd_words into cmd_words_p2
    for (int j = num_words_p1+1; j<num_words; j++)
    {
        //printf("Debug: copying command word %s to cw2.\n", cmd_words[j]);
        cmd_words_p2[j-num_words_p1-1] = cmd_words[j];
    }
    num_words_p2 = num_words - num_words_p1 - 1;
    cmd_words_p2[num_words_p2] = NULL;                // 0 marks end of words in cmd_words

    //printf("Debug: num_words_p2: %i.\n", num_words_p2);

}





int main() {

    //used to catch signals
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) != 0)
    {
        return(1);
    }


    //used for running in background
    int num = 1, backgroundrun = 0;             // backgroundrun set to 1 after % ./loop &

    int pipe_hidden[2]; // file descriptors [0] for reading [1] for writing
    pipe(pipe_hidden);
    
    int pipe_hidden2[2]; // file descriptors [0] for reading [1] for writing
    pipe(pipe_hidden2);



    //main run loop
    while(done == 0) 
    {

        backgroundrun = 0;                      // reset backgroundrun to 0 for each loop
        memset(line, 0, BUFSZ);                 // Zero line before each use

        fprintf(stdout, "mysh%d %% ", num);     // display prompt
        fflush(stdout);                         // flush prompt to terminal


        // CTL-D terminates shell but CTRL-C just sends signal to handler
        if (fgets(line, BUFSZ, stdin) == 0)
        {   
            if (sig_triggered == 1)
            {
                //printf("Debug: Not done.\n");
                //printf("\n");
                //clearerr(stdin); //lets fgets() keep running 
                sig_triggered = 0;
                continue;
            }
            else  
            {
                //printf("Debug: Done.\n");
                //printf("\n");
                break;
            }                              
        }



        

        // trim new line character from line
        line[strcspn(line, "\n")] = '\0';       


        //check if command needs to run in the background
        //check for & at end of the line. if so, remove it and make backgroundrun = 1;
        //printf("Debug: line before checking for &: %s\n",line );
        if(strcspn(line, "&") == strlen(line))
        {
            //printf("Debug: & not found at end\n");
            //printf("Debug: length: %i\n",(int)strlen(line) );
            //printf("Debug: & at: %i\n", (int)strcspn(line, "&") );
        } else 
        {
            //printf("Debug: & found\n");
            //printf("Debug: length: %i\n",(int)strlen(line) );
            //printf("Debug: & at: %i\n", (int)strcspn(line, "&") );
            backgroundrun = 1;
            // trim & from line
            line[(int)strcspn(line, "&")]='\0';
        }        
        //printf("Debug: line after removing &: %s\n",line );



        // if cd or pwd or a blank line, keep going
        if (cd_cmd() || pwd_cmd() || !get_cmd_words()) 
        {       
            continue;
        }



        //if line == "exit" then break
        else if (strcmp (line, "exit") == 0) 
        {
            break;
        }


        //if line contains "<" then redirect input         
        else if (check_cmd_words("<"))
        {
            //printf("Debug: redirect input\n");
            split_cmd_words();
            //check to see the < was used right
            if ( num_words_p1 == 0 || num_words_p2 != 1 )
            {
                printf("Incorrect command usage. Format: command > output file\n");
                continue;                
            }
            
            //execute program
            pid_t child1 = fork();
            if (child1 == 0) 
            {               
                //make sure command and file name exist and open file 
                int input_file;
                if ((input_file = open(cmd_words_p2[0], O_RDONLY, 0644)) < 0) 
                {
                    printf("Error opening file.\n");
                    exit(1);
                }

                //change standard input to file
                dup2(input_file, 0);

                if (backgroundrun == 1) 
                {                    
                    //dup2(pipe_hidden[0], 0);
                    //close(pipe_hidden[0]);
                    //close(pipe_hidden[1]);                                        
                    
                    dup2(pipe_hidden2[1], 1);
                    //close(pipe_hidden2[0]);
                    close(pipe_hidden2[1]);                   
                }

                //execute command
                execvp(cmd_words_p1[0], cmd_words_p1);        
                cmd_not_found(cmd_words_p1[0]);        // Successful execvp() does not return
            } 
            else
            {
                if (backgroundrun == 0) //don't wait if it is running in the background
                {
                    waitpid(child1, NULL, 0);   
                    //wait(NULL);
                    //wait(NULL);
                }
            }
        }


        //else if line contains ">" then redirect output
        else if (check_cmd_words(">"))
        {
            //printf("Debug: redirect output\n");
            split_cmd_words();

            if ( num_words_p1 == 0 || num_words_p2 != 1 )
            {
                printf("Incorrect command usage. Format: command < input file\n");                
                continue;
            }

            //execute program
            pid_t child2 = fork();
            if (child2 == 0)  
            {           
                //try to open output file
                int output_file;                
                if ((output_file = open(cmd_words_p2[0], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) 
                {
                    printf("Error opening file: %s.\n", cmd_words_p2[0]);
                    exit(1);
                }

                //change standard input to open file
                dup2(output_file, 1);

                if (backgroundrun == 1) 
                {                    
                    dup2(pipe_hidden[0], 0);
                    close(pipe_hidden[0]);
                    //close(pipe_hidden[1]);                                        
                    
                    //dup2(pipe_hidden2[1], 1);
                    //close(pipe_hidden2[0]);
                    //close(pipe_hidden2[1]);                   
                }

                execvp(cmd_words_p1[0], cmd_words_p1);        
                cmd_not_found(cmd_words_p1[0]);        // Successful execvp() does not return
            }
            else
            {
                if (backgroundrun == 0) //don't wait if it is running in the background
                {
                    waitpid(child2, NULL, 0);
                }
            }
        }



        //else if line contains "|" then pipe commands together
        else if (check_cmd_words("|"))
        {
            //printf("Debug: piping commands\n");
            split_cmd_words();

            if ( num_words_p1 == 0 || num_words_p2 == 0 )
            {
                printf("Incorrect command usage. Format: command | command\n");
                continue;                
            }
            //needs to fork and execute each side of pipe
     
            //create pipe
            int pipe_fd[2]; // file descriptors [0] for reading [1] for writing
            pipe(pipe_fd);
            pid_t child3; 
            pid_t child4; 

            //create child 1. This is the writer child. 
            child3 = fork();
            if (child3 == 0) //if process returned from fork is 0, it is the child
            {
                //exec p1 to pipe
                //change standard output to pipe
                dup2(pipe_fd[1], 1);
                close(pipe_fd[0]);
                close(pipe_fd[1]);

                if (backgroundrun == 1) 
                {                    
                    dup2(pipe_hidden[0], 0);
                    close(pipe_hidden[0]);
                    //close(pipe_hidden[1]);                                        
                    
                    //dup2(pipe_hidden2[1], 1);
                    //close(pipe_hidden2[0]);
                    //close(pipe_hidden2[1]);                   
                }

                execvp(cmd_words_p1[0], cmd_words_p1);        
                cmd_not_found(cmd_words_p1[0]);        // Successful execvp() does not return
                  
            }
            else //if process returned from fork is a number, it is the pid of the parent 
            {
                //create child 2. this is the read child.
                child4 = fork();
                if (child4 == 0) //if process returned from fork is 0, it is the child
                {   
                    //change standard input to pipe
                    dup2(pipe_fd[0], 0);
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);

                    if (backgroundrun == 1) {                    
                        //dup2(pipe_hidden[0], 0);
                        //close(pipe_hidden[0]);
                        //close(pipe_hidden[1]);                                        
                        
                        dup2(pipe_hidden2[1], 1);
                        //close(pipe_hidden2[0]);
                        close(pipe_hidden2[1]);                   
                    }

                    execvp(cmd_words_p2[0], cmd_words_p2);        
                    cmd_not_found(cmd_words_p2[0]);        // Successful execvp() does not return
                }
                else //if process returned from fork is a number, it is the pid of the parent 
                {
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                    
                    if (backgroundrun == 0) //don't wait if it is running in the background
                    {
                        waitpid(child3, NULL, 0);
                        waitpid(child4, NULL, 0);
                    }
                }                    
            }
        }


        //else basic command
        else 
        {
            //printf("Debug: basic command: %s\n", line);
            pid_t child5; 
            child5 = fork();
            if (child5 == 0) 
            {    
                if (backgroundrun == 1) 
                {                    
                    dup2(pipe_hidden[0], 0);
                    close(pipe_hidden[0]);                    
                    
                    dup2(pipe_hidden2[1], 1);
                    close(pipe_hidden2[1]);
                }

                execvp(cmd_words[0], cmd_words);        
                cmd_not_found(cmd_words[0]);        // Successful execvp() does not return
            }
            else 
            {   
                if (backgroundrun == 0) //don't wait if it is running in the background
                {
                    //printf("Debug: waiting on pid %i\n", (int)child5);
                    test_wait = waitpid(child5, NULL, 0);
                    //printf("Debug: waitpid result %i\n", test_wait);

                }
            }
                            
        }
        num++;                                  // command number, blank lines do not increment num
    }
    return (0);
}





