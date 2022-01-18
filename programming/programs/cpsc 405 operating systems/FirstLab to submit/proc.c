#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "proc.h"
#include "split.h"

/*
 * kernel_proc is the initial process
 * kernel_proc is created by the bootstrap function
 * kernel_proc is created by the following function call
 * kernel_proc = new_proc("kernel_process", 0, 0);
 * kernel_proc has a priority of 0 and will always be the first process in the queue
 */
struct proc *kernel_proc;

/*
 * pid is used to allocate process ids.
 * The pid of kernel_process is 1024
 * pid is incremented as processes are created
 */
int pid = START_PID;


/*
 * state_to_string converts an enum procstate to a printble C string
 */
char *state_to_string(enum procstate ps) {

    //printf("Starting state_to_string function.\n");

    switch (ps) {
        case EMBRYO:
            return "EMBRYO";
        case SLEEPING:
            return "SLEEPING";
        case RUNNABLE:
            return "RUNNABLE";
        case RUNNING:
            return "RUNNING";
        case ZOMBIE:
            return "ZOMBIE";
        case UNUSED:
            return "UNUSED";
        default:
            return NULL;
    }
}



////////////////////////////////////////////////////////DONE
/*
 * find_proc searches the linked list of procs and returns the struct proc with pid
 * find_proc returns NULL is pid is not in the linked list
 */
struct proc *find_proc(int pid) {
    
    //printf("Starting find_proc function.\n");
    
    //create placeholder_proc to traverse the linked list
    struct proc *placeholder_proc = kernel_proc;

    //go through linked list and return struct if pid matches
    do {    

        //printf("placeholder_proc->pid in list: ");
        //printf("%d", placeholder_proc->pid);
        //printf("\n");

        //printf("pid to search for: ");
        //printf("%d", pid);
        //printf("\n");

        if (placeholder_proc->pid == pid) {

            //printf("Found pid struct for: ");
            //print_proc(placeholder_proc);

            return placeholder_proc;
        }
        else 
        {

            //printf("Proc does not match pid: ");
            //print_proc(placeholder_proc);

            placeholder_proc=placeholder_proc->next;
            //printf("Moving to next proc: ");
            //print_proc(placeholder_proc);

        }
    } while (placeholder_proc != NULL);

    //printf("No pid found.\n");
    return NULL;
}



/*
 * print_proc prints to stdout a struc proc pointer
 */
void print_proc(struct proc *p) {
    
    //printf("Running print_proc function\n");

    if (p == NULL || p->parent == NULL)
        return;
    printf("pname: %s, pid: %d, ppid: %d, priority: %d, state: %s\n", p->name, p->pid, p->parent->pid, p->priority, state_to_string(p->state));
    
    /*
    printf("pname: %s, priority: %d, pid: %d, ", p->name, p->priority, p->pid);
    if(p->next != NULL)
        printf("next: %s, ", p->next->name);
    if(p->prev != NULL)
        printf("prev: %s, ", p->prev->name);
    if(p->parent != NULL)
        printf("parent: %s, ", p->parent->name);
    printf("state: %s", state_to_string(p->state));
    printf("\n");
    */
    
}


/*
 * print_pid prints to stdout the proc corresponding to pid
 */
void print_pid(int pid) {
    
    //printf("Running print_pid function\n");

    struct proc *p = find_proc(pid);
    if (p != NULL)
        print_proc(p);
    else
        printf("pid: %d not found.\n", pid);
}



/*
 * print_procs prints the entire list of procs
 */
void print_procs() {
    
    //printf("Running print_procs function\n");

    //printf("pid: %d\n", pid);
    printf("procs in queue:\n");

    struct proc *p = kernel_proc;
    do {
        print_proc(p);
        p = p->next;
    } while (p != NULL);
    printf("\n");
}



///////////////////////////////////////////////////////////////// DONE
/*
 * new_proc constructs a struc proc from the heap and returns a pointer to it
 * new_proc has to malloc a struct context and a struct proc
 * Initializing most struct proc members is straight forward.
 * For kernel_proc, p->parent points to kernel_proc.
 * For other procs, you have to search for p->parent in the list.
 */
struct proc *new_proc(char name[], uint priority, int ppid) {

    //printf("Starting new_proc function.\n");


    //create temp process
    struct proc *temp_proc = NULL; 
    temp_proc = (struct proc *)malloc(sizeof(struct proc)); 
  
    //assign values to temp process
    //temp_proc->name = name;
    strcpy (temp_proc->name, name);
    temp_proc->priority = priority;

    //assign pid and then increment for the next one
    temp_proc->pid = pid;
    pid++; 


    //assign state. runnable if kernel_proc, else embryo
    if (temp_proc->pid==1024)
    {
        temp_proc->state = RUNNABLE;        
    }
    else
    {
        temp_proc->state = EMBRYO;
    }

    
    //printf("new_proc, temp_proc: ");
    //print_proc(temp_proc);

    //look up and assign parent struct using ppid
    //assign parent to 0 if it is kernel_prod (pid=0)
    if (temp_proc->pid==1024)
    {
        temp_proc->parent=temp_proc;        
    }
    else
    {
        temp_proc->parent=find_proc(ppid);
        if (temp_proc->parent == NULL)
            return NULL;
    }

    return temp_proc;
}



////////////////////////////////////////////////// DONE
/*
 * enqueue_proc places a proc properly within the linked list of procs based upon the priority.
 */
bool enqueue_proc(struct proc *p) {
        
    //printf("Starting enqueue_proc function.\n");
    
    //create placeholder_proc to traverse the linked list
    struct proc *placeholder_proc = kernel_proc;

    //printf("enqueue_proc, p: ");
    //print_proc(p);

    //if placeholder_proc->next exists (you are not at the end of the list), traverse the linked list until next = null or if p priority is greater than placeholder priority

    while (placeholder_proc->next != NULL) {
        
        placeholder_proc=placeholder_proc->next;
        
        //printf("Moving to the next node:");
        //print_proc(placeholder_proc);
        //printf("\n");

        if (p->priority < placeholder_proc->priority) 
        {    
            placeholder_proc->prev->next=p;
            p->next=placeholder_proc;
            p->prev=placeholder_proc->prev;
            placeholder_proc->prev=p;
            
            //printf("Adding node in the middle: ");
            //print_proc(p);            
            
            return true;
        } 
    };

    //if at the end of the linked list, place the node there, at the end of placeholder
    //else place the p node before the placeholder node
   
    p->prev = placeholder_proc;
    placeholder_proc->next = p;
    
    //printf("Adding node at the end: ");
    //print_proc(p);            
    
    return true;
    
}

/*
 * bootstrap is called to initialize the doubly linked list of procs
 */ 
void bootstrap() {

    //printf("Starting boostrap function.\n");
    
    kernel_proc = new_proc("kernel_process", 0, 0);
    kernel_proc->parent = kernel_proc;
    kernel_proc->state = RUNNABLE;
}



///////////////////////////////////////////////WORKING
/*
 * kill removes a proc from the double linked list based upon pid
QUESTIONS:
Should it unallocate the memory of the process?
Should it get rid of all references to it as a parent/process?
Should it kill all orphaned processes?
 */

bool kill(int pid) {
    

    //printf("Starting kill function.\n");
    
    //create placeholder_proc to traverse the linked list
    struct proc *placeholder_proc = kernel_proc;

    //go through linked list and return struct if pid matches
    do {    

        /*
        printf("placeholder_proc->pid in list: ");
        printf("%d", placeholder_proc->pid);
        printf("\n");

        printf("pid to search for: ");
        printf("%d", pid);
        printf("\n");
        */

        if (placeholder_proc->pid == pid) {

            //printf("Found pid struct. Killing: ");
            //print_proc(placeholder_proc);

            //remove node from linked list
            if (placeholder_proc->next != NULL)
            {
                placeholder_proc->next->prev=placeholder_proc->prev;
            }
            if (placeholder_proc->prev != NULL)
            {
                placeholder_proc->prev->next=placeholder_proc->next;
            }

            return true;
        }
        else 
        {

            //printf("Proc does not match pid: ");
            //print_proc(placeholder_proc);

            placeholder_proc=placeholder_proc->next;
            
            //printf("Moving to next proc: ");
            //print_proc(placeholder_proc);

        }
    } while (placeholder_proc != NULL);

    //printf("No pid found.\n");
    
    //return 0 if no match is found
    return false;

}



/////////////////////////////////////////////////DONE
/*
 * get_pid returns the pid corresponding to a process name. 
 * get_pid returns 0 if the process name is not in the doubly linked list
 */
int get_pid(char name[]) {

    //printf("Starting get_pid function.\n");
    
    //create placeholder_proc to traverse the linked list
    struct proc *placeholder_proc = kernel_proc;

    //go through linked list and return pid if name matches
    do {    

        //printf("placeholder_proc->name in list: ");
        //printf("%s", placeholder_proc->name);
        //printf(", name to search for: ");
        //printf("%s", name);
        //printf("\n");


        if ((strcmp(placeholder_proc->name, name)) == 0) {

            //printf("Found pid for: ");
            //print_proc(placeholder_proc);

            return placeholder_proc->pid;
        }
        else 
        {

            //printf("Proc does not match name: ");
            //print_proc(placeholder_proc);

            placeholder_proc=placeholder_proc->next;
            //printf("Moving to next proc: ");
            //print_proc(placeholder_proc);

        }
    } while (placeholder_proc != NULL);

    //printf("No pid found.\n");

    //return 0 if no match is found
    return 0;
}



/*
 * fork creates a new process and enqueues it in the doubly linked list
 */
int fork(char name[], int priority, int ppid) {

    //printf("\n\nStarting fork function.\n");

    if (priority <= 0)
        return 0;
    struct proc *p = new_proc(name, priority, ppid);



    if (p != NULL)
        if (enqueue_proc(p))
            return p->pid;
    return 0;
}
