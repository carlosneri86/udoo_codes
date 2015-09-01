#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h> 
#include <stdint.h>
#include <stdlib.h>


#define MQ_MODE       (S_IRWXU | S_IRWXG | S_IRWXO)


#define INCREMENT_COMMAND	('i')
#define MAX_MESSAGES		(10)
#define	MAX_MESSAGES_SIZE	(10)
#define COMMAND_BUFFER_SIZE	(MAX_MESSAGES * MAX_MESSAGES_SIZE)


/*Function used for the threads*/
void *vfnThreadPrint( void *ptr );
void *vfnThreadIncrement( void *ptr );


int main (int argc, char *argv[])
{
	int flags = 0;
	struct mq_attr queue_attributes;
	mqd_t mqd;
	pthread_t ThreadPrint;
	pthread_t ThreadIncrement;


	flags |=  O_CREAT|O_RDWR;
	queue_attributes.mq_maxmsg = MAX_MESSAGES;
	queue_attributes.mq_msgsize = MAX_MESSAGES_SIZE;
	queue_attributes.mq_flags = 0;
 
	mqd = mq_open("/Message_queue_test", flags, MQ_MODE,&queue_attributes);


	if(mqd < 0)
	{

		perror("MessageCreate");

	}
	/* Create independent threads each of which will execute function */

	(void)pthread_create(&ThreadPrint, NULL, &vfnThreadPrint, (void*)&mqd);
	(void)pthread_create(&ThreadIncrement, NULL, &vfnThreadIncrement, (void*)&mqd);


	while(1)
	{


	}	
}


void *vfnThreadPrint( void *ptr )
{
	mqd_t * messagequeue = (mqd_t*)ptr;
	char * pbCommandBuffer = (char*)malloc(COMMAND_BUFFER_SIZE);

	printf("Increment Message Queue ID: %d", *messagequeue);
	while(1)
	{
		printf("Write a command:\n");
		fgets(pbCommandBuffer,COMMAND_BUFFER_SIZE,stdin);
		
		(void)mq_send(*messagequeue,pbCommandBuffer,1,0);
		
	}
}

void *vfnThreadIncrement( void *ptr )
{

	mqd_t * messagequeue = (mqd_t*)ptr;
	char * pbRxBuffer = (char *)malloc(COMMAND_BUFFER_SIZE);
	uint32_t dwCounter = 0;
	int32_t RxStatus;
	
	printf("Increment Message Queue ID: %d", *messagequeue);

	while(1)
	{
		
		RxStatus = mq_receive(*messagequeue,pbRxBuffer,COMMAND_BUFFER_SIZE,NULL);
		if(RxStatus > 0)
		{
			if(*pbRxBuffer  == INCREMENT_COMMAND)
			{
				dwCounter++;
				printf("Incrementing Counter: %d\n",dwCounter);
			}
			else
			{
				printf("Wrong Command\n");
			}
		}
		else
		{
			perror("ReadMSG");
		}
	}
}
