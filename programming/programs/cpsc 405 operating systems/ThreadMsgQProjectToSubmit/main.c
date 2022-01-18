//compile with gcc -pthread -o main -Wall main.c zemaphore.o

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "zemaphore.h"
//#include "msgq.h"

// SEE Labs/GdbLldbLab for more information on lldb - lowlevel debugger
#define MSGQLEN 4

/* You must design and implement struct msgq, which must involve dynamically allocated
memory. My solution includes a linked list of messages, where send_msg mallocs memory for
the data structure and places it on the end of the linked list. The data structure has a char*
pointer to the message. The heap memory for the message is allocated using strdup.
recv_msg removes the head from the linked list and returns the char* pointer to the message.*/


//linked list structure to hold the messgaes
struct list {
    struct list *next;
    char *message;
};  


//message queue
struct msgq {
	struct list *head;
	struct list *tail;
	zem_t *msem; // used for functions withing functions
	zem_t *msem2; // used for functions
    zem_t *empty; // used for functions
    zem_t *full; // used for functions
    int mlength;
    int mmaxlength;
};  

struct msgq *mq;



// initializes a message queue and returns a pointer to a struct msgq. The parameter num_msgs is the maximum number of messages that may be in the message queue. The returned pointer is used in the other API functions.
struct msgq *msgq_init(int num_msgs)
{
	//printf("Debug: Running msgq_init\n");

	mq = malloc(sizeof(struct msgq));

	mq->head = NULL;
	mq->tail = NULL;
	mq->mlength = 0;
	mq->mmaxlength = num_msgs;
	
	mq->msem = malloc(sizeof(struct __zem_t));
	zem_init(mq->msem, 1);

	mq->msem2 = malloc(sizeof(struct __zem_t));
	zem_init(mq->msem2, 1);

    mq->empty = malloc(sizeof(struct __zem_t));
    zem_init(mq->empty, MSGQLEN);

    mq->full = malloc(sizeof(struct __zem_t));
    zem_init(mq->full, 0);

	return mq;
} 



// places msg on message queue mq. mq is returned from msgq_init. msgq_send must make a copy of msg on the heap. If mq has num_msgs in it; then msgq_send blocks until there is room for msg. msgq_send returns 1 for success and -1 for failure. mallocs memory for the data structure and places it on the end of the linked list
int msgq_send(struct msgq *mq, char *msg)
{
	//printf("Debug: Running msgq_send\n");

	struct list *t = malloc(sizeof(struct list)); // could return -1 if malloc fails
    
    if (t == NULL || msg == NULL) // if malloc fails 
    {
        return -1;
    }
    else
    {
    	
        zem_wait(mq->empty); 
	    zem_wait(mq->msem); 

    	if ( mq->head == NULL && mq->tail == NULL ) // if nothing is in the queue yet
    	{
	    	mq->head = t; // make head equal to new item
			mq->tail = t; // and make tail equal to new item
    	}
    	else //add new item to the tail of the queue
    	{
    		mq->tail->next = t; 
    		mq->tail = t;
    	}

	    t->message = strdup(msg);
    
        t->next = NULL;
        
	    mq->mlength++;
	
	    zem_post(mq->msem); 
        zem_post(mq->full); 
    
	    return 1;
    }
} 



// returns a message from mq. mq is returned from msgq_init. The returned message is on the heap. The function that receives the message can free it when it is no longer needed.
char *msgq_recv(struct msgq *mq) 
{
	//printf("Debug: Running msgq_recv\n");
	
	char *return_message;

    zem_wait(mq->full); 
    zem_wait(mq->msem); 

	if (mq->head != NULL)
	{
		return_message = mq->head->message;
        mq->head = mq->head->next;
        //if head is NULL then set tail to NULL too because there is nothing left
        if (mq->head == NULL) 
        {
            mq->tail = NULL;
        }
        mq->mlength--; 
	}
    
    zem_post(mq->msem); 
    zem_post(mq->empty); 
	return return_message;
} 



// returns the number of messages on mq. mq is returned from msgq_init. Due to the nature of threads and interrupts, the length returned may be incorrect by the time it is used.
int msgq_len(struct msgq *mq) 
{
	//printf("Debug: Running msgq_len\n");
	return mq->mlength;
} 



// displays all of the messages in mq to stdout. mq is returned from msgq_init.
void msgq_show(struct msgq *mq) 
{
	//printf("Debug: Running msgq_show\n");
    zem_wait(mq->msem); 

	if (mq->head == NULL) 
	{
        printf("There are no messages.\n");
	} 
	else
	{
		struct list *current_list_item = mq->head;
        while (current_list_item != NULL) 
        {
            printf("%s\n", current_list_item->message);
            current_list_item = current_list_item ->next;
        }
	}

    zem_post(mq->msem); 
} 



char *messages[] = { "msg1", "msg2", "hellomsg", "gustymsg" };

// sends msgs in messages[]
void *promtAndSend(void *arg) {
	//printf("Debug: Running promtAndSend\n");
    zem_wait(mq->msem2); 
    for (int i = 0; i < sizeof(messages)/sizeof(char*); i++) {
        char response[80];
        printf("Send? ");
        scanf("%s", response);
        if (response[0] == 'y' || response[0] == 'Y') {
            printf("sending: %s\n", messages[i]);
            msgq_send(mq, messages[i]);
        }
    }
	zem_post(mq->msem2); 
    return NULL;
}



char *messages2[] = { "msg1", "msg2", "hellomsg", "gustymsg", "finalmessage" };

void *promtAndSend2(void *arg) {
    //printf("Debug: Running promtAndSend\n");
    zem_wait(mq->msem2); 
    for (int i = 0; i < sizeof(messages2)/sizeof(char*); i++) {
        char response[80];
        printf("Send? ");
        scanf("%s", response);
        if (response[0] == 'y' || response[0] == 'Y') {
            printf("sending: %s\n", messages2[i]);
            msgq_send(mq, messages2[i]);
        }
    }
    zem_post(mq->msem2); 
    return NULL;
}


// first index of the multi-demensional array is used for the thread number
char* messages3[2][55] = {{ "msg1", "msg2", "msg3", "msg4", "msg5", "msg6", "msg7", "msg8", "msg9", "msg10", "msg11", "msg12", "msg13", "msg14", "msg15", "msg16", "msg17", "msg18", "msg19", "msg20", "msg21", "msg22", "msg23", "msg24", "msg25", "msg26", "msg27", "msg28", "msg29", "msg30", "msg31", "msg32", "msg33", "msg34", "msg35", "msg36", "msg37", "msg38", "msg39", "msg 40", "msg41", "msg42", "msg43", "msg44", "msg45", "msg46", "msg47", "msg48", "msg49", "msg50", "msg51", "msg52", "msg53", "msg54", "msg55" },{ "msg56", "msg57", "msg58", "msg59", "msg60", "msg61", "msg62", "msg63", "msg64", "msg65", "msg66", "msg67", "msg68", "msg69", "msg70", "msg71", "msg72", "msg73", "msg74", "msg75", "msg76", "msg77", "msg78", "msg79", "msg80", "msg81", "msg82", "msg83", "msg84", "msg85", "msg86", "msg87", "msg88", "msg89", "msg 90", "msg91", "msg92", "msg93", "msg94", "msg95", "msg96", "msg97", "msg98", "msg99", "msg100", "msg101", "msg102", "msg103", "msg104", "msg105", "msg106", "msg107", "msg108", "msg109", "msg110" }};

void *promtAndSend3(void *arg) {
    //printf("Debug: Running promtAndSend\n");
    //zem_wait(mq->msem2); 
    for (int i = 0; i < sizeof(messages3[(int)arg-4])/sizeof(char*); i++) {
        printf("thread %i sending: %s\n", (int)arg, messages3[(int)arg-4][i]);
        msgq_send(mq, messages3[(int)arg-4][i]);
    }
    //zem_post(mq->msem2); 
    return NULL;
}



// consume messges in msgq
void *recvMsgs(void *arg) {
	//printf("Debug: Running recvMsgs\n");
    sleep(5);
    zem_wait(mq->msem2); 

    int msg_count = msgq_len(mq);
    printf("mq msg_count: %d\n", msg_count);
    for (int i = 0; i < msg_count; i++) {
        char *m = msgq_recv(mq);
        printf("recvMsgs: %s\n", m);
        //free(m);
    }

	zem_post(mq->msem2); 
    return NULL;
}



// consume specific number of messges in msgq
void *recvMsgsNumber(void *arg) {
    //printf("Debug: Running recvMsgs\n");
    sleep(5);
    zem_wait(mq->msem2); 

    int msg_count = (int)arg;
    printf("mq msg_count: %d\n", msg_count);
    for (int i = 0; i < msg_count; i++) {
        char *m = msgq_recv(mq);
        printf("recvMsgs: %s\n", m);
        //free(m);
    }
    zem_post(mq->msem2); 
    return NULL;
}



char *message_array[3][50];

// consume 50 messages in msgq
void *recvMsgs50(void *arg) {
    //printf("Debug: Running recvMsgs\n");
    //zem_wait(mq->msem2); 
    int msg_count = 50;
    //printf("mq msg_count: %d\n", msg_count);
    for (int i = 0; i < msg_count; i++) {
        char *m = msgq_recv(mq);
        printf("thread %i receiving: %s\n", (int)arg, m);
        message_array[(int)arg-1][i] = strdup(m);
        //free(m);
    }
    printf("thread %i finished receiving 50 messages.\n", (int)arg);
    /*    
    for (int i = 0; i < msg_count; i++) {
        printf("%s ", message_array[(int)arg-1][i]);
        //free(m);
    }
    printf("\n");
    */
    //zem_post(mq->msem2); 
    return NULL;
}



//two threads of passiton pass the messages back and forth in an infinite loop?
void *passiton(void *arg) {
    int me = (int) arg;
    //printf("Debug: Running passiton %i\n", me);

    while (1) {
        sleep(1);
        //printf("\nDebug: Passiton loop %i\n", me);
		zem_wait(mq->msem2); 
        printf("passiton%d initial msgq_len: %d\n", me, msgq_len(mq));
        
        char *m = msgq_recv(mq);
        
        printf("passiton%d: %p %p %s\n", me, &m, m, m);
        printf("passiton%d after recv msgq_len: %d\n", me, msgq_len(mq));
        msgq_send(mq, m);
        printf("passiton%d after send msgq_len: %d\n", me, msgq_len(mq));
        
        zem_wait(mq->msem);             // wait for access to critical region
        free(m);
        zem_post(mq->msem);             // exit critical region
        
        zem_post(mq->msem2); 
    }
    return NULL;
}





int main(int argc, char *argv[]) {
	//printf("Debug: Running main\n");

    pthread_t p1, p2, p3, p4, p5;
    mq = msgq_init(MSGQLEN);
    char test = '1';
    if (argc == 2)
        test = argv[1][0];
    switch (test) {
      case '1':
        printf("test fill and empty msgq\n");
        pthread_create(&p1, NULL, promtAndSend, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 1:\n");
        msgq_show(mq);
        pthread_create(&p2, NULL, recvMsgs, NULL);
        pthread_join(p2, NULL);
        printf("msgq_show() after all consumed by test 1:\n");
        msgq_show(mq);
        break;

    case '2':
        printf("test fill msgs and pass it on\n");
        pthread_create(&p1, NULL, promtAndSend, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 2:\n");
        msgq_show(mq);
        pthread_create(&p1, NULL, passiton, (void *)1);
        pthread_create(&p2, NULL, passiton, (void *)2);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
        break;

    //Show that send_msg blocks when the message queue contains num_msgs.
    case '3':
        printf("test fill msgs and pass it on\n");
        pthread_create(&p1, NULL, promtAndSend2, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 1:\n");
        msgq_show(mq);
        pthread_create(&p2, NULL, recvMsgsNumber, (void *)4);
        pthread_join(p2, NULL);
        printf("msgq_show() after all consumed by test 1:\n");
        msgq_show(mq);
        break;

    //Show that recv_msg blocks when the message queue is empty.
    case '4':
        printf("test fill msgs and pass it on\n");
        pthread_create(&p1, NULL, promtAndSend, NULL);
        pthread_join(p1, NULL);
        printf("msgq_show() after filling for test 1:\n");
        msgq_show(mq);
        pthread_create(&p2, NULL, recvMsgsNumber, (void *)6);
        pthread_join(p2, NULL);
        printf("msgq_show() after all consumed by test 1:\n");
        msgq_show(mq);
        break;

    /* Solve a producer consumer problem with your message queue and five threads. Two
    threads are producers generating messages and three threads are consumers
    consuming messages. Each producer must generate at least 50 messages. You shall
    use the same function code for the two producers. An argument passed is used to select
    the messages that are generated. The consumers shall save their consumed messages
    in static arrays - one for each consumer. You shall use the same function code for the
    three consumers. An argument passed is used to select the static array to store the
    messages. Main shall wait for the two producers to finish and then wait an additional
    five seconds, at which point the three consumers should be blocked on msgq_recv calls.
    Main shall print the messages received in each consumer. Ensure that all 100 messages
    are consumed. Experiment to determine which consumers consume which messages.*/
    case '5':
        pthread_create(&p4, NULL, promtAndSend3, (void *)4);
        pthread_create(&p5, NULL, promtAndSend3, (void *)5);

        pthread_create(&p1, NULL, recvMsgs50, (void *)1);
        pthread_create(&p2, NULL, recvMsgs50, (void *)2);
        pthread_create(&p3, NULL, recvMsgs50, (void *)3);

        //pthread_join(p1, NULL);
        //pthread_join(p2, NULL);
        //pthread_join(p3, NULL);
        pthread_join(p4, NULL);
        pthread_join(p5, NULL);

        sleep(5);

        //print the arrays of messages
        for (int x = 0; x < 3; x++) 
        {
            printf("thread %i received these messages: ", x+1);
            for (int y = 0; y < 50; y++) {
                if (message_array[x][y])
                    printf("%s ", message_array[x][y]);
            }
            printf("\n");
        }
        break;

    default:
        printf("invalid test selection!\n");
        break;
    }
    return 0;
}

