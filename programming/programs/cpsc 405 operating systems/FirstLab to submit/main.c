#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "proc.h"
#include "split.h"

#define BUFFER_LEN 100

int main() {
    bootstrap();
    
    char line[BUFFER_LEN]; //the line of text being read

    //while more lines of text exist, read them and run the corresponding function
    while (fgets(line, BUFFER_LEN, stdin) != NULL) {

        //printf("\n---------\n");
        line[strlen(line)-1] = 0; // remove \n from line
        if (line[0] == '#')
            continue;

        struct proc *p = NULL;
        int num;
        
        //create an array of words from the line. it updates num with the number of strings in the line I think but never uses it later.
        //proc_stuff is made up of [0] process, [1] name, [2] priority, [3] parent name
        //example: fork Zac 3 Gusty
        char **proc_stuff = split(line, " ", &num);
        

        //run different function depending on the process name
        if (strcmp(proc_stuff[0],"fork") == 0){
            //printf("Main, get pid of %s %s %s\n", proc_stuff[1], proc_stuff[2], proc_stuff[3]);
            fork(proc_stuff[1], atoi(proc_stuff[2]), get_pid(proc_stuff[3]));
        }

        else if (strcmp(proc_stuff[0],"kill") == 0)
            kill(get_pid(proc_stuff[1]));
        
        else if (strcmp(proc_stuff[0],"printpid") == 0) {
            p = find_proc(get_pid(proc_stuff[1]));
            if (p != NULL)
                printf("procname: %s, pid: %d\n", proc_stuff[1], p->pid);
            else
                printf("procname: %s not found\n", proc_stuff[1]);
        }
        
        else if (strcmp(proc_stuff[0],"printppid") == 0) {
            p = find_proc(get_pid(proc_stuff[1]));
            if (p != NULL)
                printf("procname: %s, ppid: %d\n", proc_stuff[1], p->parent->pid);
            else
                printf("procname: %s not found\n", proc_stuff[1]);
        }
        
        else if (strcmp(proc_stuff[0],"printprocs") == 0)
            print_procs();
    }
}
            
    

