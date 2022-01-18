// added prio_to_weight array for translating nice values.
// added three variables to struct ptable. 
// added slight tweak to Exit, Sleep, Wakeup and Fork to reset scheduler when they run
// added Nice function to change nice value for a process
// added countprocs function to count the number of running/runnable processes
// rewrote the scheduler function
// modified procdump to add nice value and vruntime


/*****************************************************************
*       proc.c - simplified for CPSC405 Lab by Gusty Cooper, University of Mary Washington
*       adapted from MIT xv6 by Zhiyi Huang, hzy@cs.otago.ac.nz, University of Otago
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "defs.h"
#include "proc.h"

static void wakeup1(int chan);


// used to translate nice value to weight
static const int prio_to_weight[40] = {
 /* -20 */     88761,     71755,     56483,     46273,     36291,
 /* -15 */     29154,     23254,     18705,     14949,     11916,
 /* -10 */      9548,      7620,      6100,      4904,      3906,
 /*  -5 */      3121,      2501,      1991,      1586,      1277,
 /*   0 */      1024,       820,       655,       526,       423,
 /*   5 */       335,       272,       215,       172,       137,
 /*  10 */       110,        87,        70,        56,        45,
 /*  15 */        36,        29,        23,        18,        15,
};


// Dummy lock routines. Not needed for lab
void acquire(int *p) {
    return;
}
// Dummy lock routines 2. Not needed for lab
void release(int *p) {
    return;
}


// enum procstate for printing
char *procstatep[] = { "UNUSED", "EMPRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE" };


// Table of all processes 
struct {
  int lock;   // not used in Lab
  struct proc proc[NPROC]; // an array of processes


  //added by me for completely fair scheduler
  int sched_latency;      // The time that the scheduler will loop through all processes if all things equal. 
                               // Time to run each process should be scheduler_latency/number of processes. Then it needs to check for next process to run. 
                               // There needs to be a minimun per process. 
  int min_granularity;     // The minimum length of time a process can run
  int time_slice;             // The time to run before looking for a new process to run.
  
  //countprocs() keeps track number of processes that are running rather than having a separate variable to maintain 

} ptable;


// Initial process - ascendent of all other processes
static struct proc *initproc;


// Used to allocate process ids - initproc is 1, others are incremented
int nextpid = 1;


// Funtion to use as address of proc's PC
void forkret(void)
{
}


// Funtion to use as address of proc's LR
void trapret(void)
{
}


// Initialize the process table
//fills the ptable with 0s
void
pinit(void)
{
  memset(&ptable, 0, sizeof(ptable));
}

// Look in the process table for a process id
// If found, return pointer to proc
// Otherwise return 0.
static struct proc*
findproc(int pid)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->pid == pid)
      return p;
  return 0;
}


// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;

  p->context = (struct context*)malloc(sizeof(struct context));
  memset(p->context, 0, sizeof *p->context);
  p->context->pc = (uint)forkret;
  p->context->lr = (uint)trapret;

  return p;
}


// Set up first user process.
int userinit(void)
{
  struct proc *p;
  p = allocproc();
  initproc = p;
  p->sz = PGSIZE;
  strcpy(p->cwd, "/");
  strcpy(p->name, "userinit"); 
  p->state = RUNNING;
  curr_proc = p;
  return p->pid;
}


// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int Fork(int fork_proc_id)
{
  int pid;
  struct proc *np; //new process (child)
  struct proc *fork_proc; //process being forked (parent)

  // Find current proc
  if ((fork_proc = findproc(fork_proc_id)) == 0)
    return -1;

  // Allocate process.
  if((np = allocproc()) == 0)
    return -1;

  // Copy process state from p.
  np->sz = fork_proc->sz;
  np->parent = fork_proc;
  // Copy files in real code
  strcpy(np->cwd, fork_proc->cwd);
 
  pid = np->pid;
  np->state = RUNNABLE;
  strcpy(np->name, fork_proc->name);

  //copy vruntime from parent to new process
  np->vruntime = fork_proc->vruntime; 

  //reset scheduler and get new process running
  ptable.time_slice = 0;
  scheduler();

  return pid;
}


// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
int Exit(int exit_proc_id)
{
  struct proc *p, *exit_proc;

  // Find current proc
  if ((exit_proc = findproc(exit_proc_id)) == 0)
    return -2;

  if(exit_proc == initproc) {
    printf("initproc exiting\n");
    return -1;
  }

  // Close all open files of exit_proc in real code.

  acquire(&ptable.lock);

  wakeup1(exit_proc->parent->pid);

  // Place abandoned children in ZOMBIE state - HERE
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == exit_proc){
      p->parent = initproc;
      p->state = ZOMBIE;
    }
  }

  exit_proc->state = ZOMBIE;

  // sched();
  //reset scheduler
  ptable.time_slice = 0;

  release(&ptable.lock);
  return 0;
}


// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
// Return -2 has children, but not zombie - must keep waiting
// Return -3 if wait_proc_id is not found
int Wait(int wait_proc_id)
{
  struct proc *p, *wait_proc;
  int havekids, pid;

  // Find current proc
  if ((wait_proc = findproc(wait_proc_id)) == 0)
    return -3;

  acquire(&ptable.lock);
  for(;;){ // remove outer loop
    // Scan through table looking for zombie children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != wait_proc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        p->kstack = 0;
        p->state = UNUSED;
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || wait_proc->killed){
      release(&ptable.lock);
      return -1;
    }
    if (havekids) { // children still running
      Sleep(wait_proc_id, wait_proc_id);
      release(&ptable.lock);
      return -2;
    }

  }
}


// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
int Sleep(int sleep_proc_id, int chan)
{
  struct proc *sleep_proc;
  // Find current proc
  if ((sleep_proc = findproc(sleep_proc_id)) == 0)
    return -3;

  sleep_proc->chan = chan;
  sleep_proc->state = SLEEPING;

  //reset scheduler and get new process running
  ptable.time_slice = 0;
  scheduler();

  return sleep_proc_id;
}


// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void wakeup1(int chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
    {
      p->state = RUNNABLE;
      p->vruntime = curr_proc->vruntime; //set proc to minimum vruntime so it does not run for a long time when it awakens
    }
}


void Wakeup(int chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);

  //reset scheduler and get new process running
  ptable.time_slice = 0;
  scheduler();

  release(&ptable.lock);
}



// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int Kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}




// Set the nice value of the given pid.
// return 0 if success or -1 if pid not found or nice value out of range
int Nice(int pid, int new_nice)
{
  struct proc *p;

  acquire(&ptable.lock);

  //check to see new nice value is between -20 and 19. default is 0.
  if (new_nice >=-20 && new_nice <= 19)
  {
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->pid == pid){
        p->nice = new_nice;
        return 0;
      }
    }
  }
  printf("Pid must exist. Nice value must be -20 (high priority) to 19 (low priority).\n");
  release(&ptable.lock);
  return -1;
}





// Counts the number of processes that are runnable or running and not killed
int get_total_weight(void)
{
  int total_weight = 0;
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
  {
    if(p->pid > 0 && (p->state == RUNNABLE || p->state == RUNNING) && p->killed == 0)
    {
      total_weight = total_weight + prio_to_weight[(p->nice)+20];
    }
  }
  return total_weight;
}



///////////////////////////////////////////////////////////////////////////////
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.

// it changes current_proc to the new process that needs to run. the one with the lowest vruntime

void scheduler(void)
{
// A continous loop in real code
//  if(first_sched) first_sched = 0;
//  else sti();

//if it is time to schedule a new process (time_slice <= 0) then schedule a new process
//else reduce time_slice by one

if (ptable.time_slice <= 1) 
{

    printf("Running scheduler.\n");
    //stop current process from running
    if (curr_proc->state == RUNNING)
    {
      curr_proc->state = RUNNABLE;
    }

    struct proc *p; //used to search procs
    struct proc *p_lowest_vruntime; //used to hold value of the process with the lowest vruntime, which will run next

    //set process with the lowest vruntime as current by default
    p_lowest_vruntime = curr_proc;

    acquire(&ptable.lock);

    //find process with the lowest vruntime
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      
      //if current process is not runnable, the next process that is and make it the current process
      if (curr_proc->state == RUNNABLE){      

        //if p(the current)->vruntime < p_lowest_vruntime(the record low)->vruntime then
        if (p->vruntime < p_lowest_vruntime->vruntime && p->killed==0 && p->state==RUNNABLE)
        {
          //set the current to the record low. p_lowest_vruntime = p
          p_lowest_vruntime = p;
        }
      }
      else //if the current process is not runnable, set it to the next runnable process  
      {
        if (p->killed==0 && p->state==RUNNABLE)
        {
          curr_proc = p;
          p_lowest_vruntime = p;
        }
      }
    }

    // Switch to chosen process and make it running if possible.
    curr_proc = p_lowest_vruntime;
    if (curr_proc->state == RUNNABLE)
    {
      curr_proc->state = RUNNING;

      //set new time_slice value
      //time_slice = sched_latency / countprocs() or min_granularity, whichever is greater
      ptable.sched_latency = 48; 
      ptable.min_granularity = 6;

      //calculate time slice for process (process weight / sum of all process weights * sched_latency)
      //printf("Process weight: %i\n", prio_to_weight[(curr_proc->nice)+20]);
      //printf("Total weight: %i\n", get_total_weight());
      ptable.time_slice = ptable.sched_latency * prio_to_weight[(curr_proc->nice)+20] / get_total_weight(); //put division at the end of the equation because I was getting 0 before because they were integers.
      
      if ( ptable.time_slice < ptable.min_granularity )
      {
        ptable.time_slice = ptable.min_granularity;
      }
      printf("Time slice: %i\n", ptable.time_slice);
    }
    
    release(&ptable.lock);

  } 
  else 
  {
    
    if (curr_proc->state == RUNNING) //if only process available is asleep, don't change vruntime or timeslice
    { 
      //when time_slice still has some time left for this proc, just keep proc instead of scheduling a new one
      ptable.time_slice--;
      
      //add vruntime using nice. vruntime added is inversely proportionate to share of total weight
      curr_proc->vruntime = curr_proc->vruntime + ( get_total_weight() - prio_to_weight[(curr_proc->nice)+20]);

    }
  }
}






// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void procdump(void)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->pid > 0)
      printf("pid: %d, parent: %d, nice: %d, vruntime: %d, state: %s\n", p->pid, p->parent == 0 ? 0 : p->parent->pid, p->nice, p->vruntime, procstatep[p->state]);
}


