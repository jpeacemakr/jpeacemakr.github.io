/*****************************************************************
*    main.c - Gusty - began with code from https://codereview.stackexchange.com/questions/67746/simple-shell-in-c
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "types.h"
#include "defs.h"
#include "proc.h"

void parseCmd(char* cmd, char** params, int *nparams);
int executeCmd(char** params, int nparams);

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10

enum cmds        { FORK=0, SETPID,   SHOWPID,    WAIT,   EXIT,   SLEEP,   WAKEUP,   PS,   SCHEDULE,   TIMER,   HELP,  TICKETS,   QUIT };
char *cmdstr[] = {"fork", "Setpid", "currpid",  "wait", "exit", "sleep", "wakeup", "ps", "schedule", "timer", "help", "tickets", "quit"};

int curr_proc_id = 0;

int local_scheduler() {
    scheduler();
    struct proc *p = curr_proc;
    return p->pid;
}

int main()
{
    pinit(); // initialize process table. Just sets block in memory to 0.
    curr_proc_id = userinit(); // create first user process

    char cmd[MAX_COMMAND_LENGTH + 1]; //string to hold command
    int cmdCount = 0; //number of commands that have been executed
    
    char* params[MAX_NUMBER_OF_PARAMS + 1]; //string to hold parameters
    int nparams = 0; //number of parameters

    while(1) {
        nparams = 0; // > Fork 4 command sets nparams to 2
        char* username = getenv("USER");
        printf("%s@shell %d> ", username, ++cmdCount);

        //get command from keyboard. if none, break.
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        
        //replace \n with \0
        if(cmd[strlen(cmd)-1] == '\n') cmd[strlen(cmd)-1] = '\0';
        
        //take command and break into parameters
        parseCmd(cmd, params, &nparams);

        //if first paramaeter is quit, break.
        if(strcmp(params[0], "Quit") == 0) break;

        //execute command. if it returns 0 (an error?), break.
        if(executeCmd(params, nparams) == 0) break;
    }

    return 0;
}




// Split cmd into array of parameters
void parseCmd(char* cmd, char** params, int *nparams)
{       
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&cmd, " ");
        if(params[i] == NULL) break;
        (*nparams)++;
    }
}


//executes a command
int executeCmd(char** params, int nparams)
{
    int pid;
    int rc = 1; //is teturned by executeCmd. 0 if to quit
    int chan;
    int ncmds = sizeof(cmdstr) / sizeof(char *);
    int cmd_index; //command index. the nmber that corresponds to the command to execute
    

    //find the command index that matches the first paramater
    for (cmd_index = 0; cmd_index < ncmds; cmd_index++)
        if (strcmp(params[0], cmdstr[cmd_index]) == 0)
            break;

    //for (int i = 0; i < nparams; i++)
        //printf("Param %d: %s\n", i, params[i]);
    //printf("ncmds: %d, cmd_index: %d\n", ncmds, cmd_index);
    


    switch (cmd_index) {

    //adds a new process based on the one that is currently running
    case FORK:
        if (nparams > 1)
            pid = atoi(params[1]);
        else
            pid = curr_proc->pid;
        int fpid = Fork(pid);
        printf("pid: %d forked: %d\n", pid, fpid);
        break;

    case SETPID:
        if (nparams == 1)
            printf("setpid cmd requires pid parameter\n");
        else
            curr_proc_id = atoi(params[1]);
        break;

    case SHOWPID:
        //printf("Current pid: %d\n", curr_proc_id);
        printf("Current pid: %d\n", curr_proc->pid);
        break;

    case WAIT:
        if (nparams > 1)
            pid = atoi(params[1]);
        else
            pid = curr_proc->pid;
        int wpid = Wait(pid);
        if (wpid == -1)
            printf("pid: %d has no children to wait for.\n", pid);
        else if (wpid == -2)
            printf("pid: %d has children, but children still running.\n", pid);
        else
            printf("pid: %d child %d has terminated.\n", pid, wpid);
        break;

    case EXIT:
        if (nparams > 1)
            pid = atoi(params[1]);
        else
            pid = curr_proc->pid;
        pid = Exit(pid);
        printf("Exit Status:: %d .\n", pid);
        break;

    //not used?
    case SLEEP:
        if (nparams < 2)
            printf("Sleep chan [pid]\n");
        else {
            chan = atoi(params[1]);
            if (nparams > 2)
                pid = atoi(params[2]);
            else
                pid = curr_proc->pid;
            pid = Sleep(pid, chan);
            printf("Sleep Status:: %d .\n", pid);
        }
        break;

    //not used?    
    case WAKEUP:
        if (nparams < 2)
            printf("Wakeup chan\n");
        else {
            chan = atoi(params[1]);
            Wakeup(chan);
        }
        break;

    //prints state of the process that are running
    case PS:
        procdump();
        break;

    //picks a new process to run    
    case SCHEDULE:
        pid = local_scheduler();
        if (curr_proc->state==RUNNING)
            printf("Scheduler selected pid: %d\n", pid);
        else 
            printf("No runnable processes.\n");
        break;

    //picks a new process to run    
    case TICKETS:
        if (nparams < 3)
        {
            printf("Usage: tickets [pid] [tickets to add]\n");
        }
        else 
        {
            if (Tickets(atoi(params[1]), atoi(params[2])) == 0)
            {
                printf("Tickets value set.\n");
            }
            else
            {
                printf("Error setting tickets value.\n");
            }
        }
        break;


    //runs schedule a selected number of times    
    case TIMER:
        if (nparams < 2)
            printf("timer quantums\n");
        else {
            int quantums = atoi(params[1]);
            for (int i = 0; i < quantums; i++) {
                pid = local_scheduler();
                if (curr_proc->state==RUNNING)
                    printf("Scheduler selected pid: %d\n", pid);
                else 
                    printf("No runnable processes.\n");
            }
        }
        break;

    case HELP:
        printf("Commands: fork, wait, exit, ps, Setpid, currpid, sleep, wakeup, timer, tickets, schedule, help\n");
        break;

    case QUIT:
        rc = 0;
        break;

    default:
        printf("Invalid command! Enter Help to see commands.\n");
    }
    
    return rc;
}
