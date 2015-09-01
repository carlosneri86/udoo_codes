#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
/*Function used for the threads*/
void *ThreadPrint( void *ptr );
void *ThreadIncrement( void *ptr );

uint32_t gu32Counter = 0;
pthread_mutex_t mymutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mymutex2 = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{
	pthread_t threadprint;
	pthread_t threadincrement;

	int32_t  threadprintID;
	int32_t  threadIncrementID;

    /* Create independent threads each of which will execute function */

     threadprintID			 = pthread_create( &threadprint, NULL, (void *)ThreadPrint, (void*) NULL);
     threadIncrementID	 = pthread_create( &threadincrement, NULL, (void *)ThreadIncrement, (void*) NULL);
	 pthread_mutex_init(&mymutex1, NULL);
	 pthread_mutex_init(&mymutex2, NULL);
     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */
	while(1)
	{
	}

     
     exit(0);
}

void *ThreadPrint( void *ptr )
{
     while(1)
	{
		//pthread_mutex_lock(&mymutex2);		
		printf("%d\n\r",gu32Counter);
		pthread_mutex_unlock(&mymutex1);
	}
}

void *ThreadIncrement( void *ptr )
{
     while(1)
	{
		pthread_mutex_lock(&mymutex1);		
		gu32Counter++;
		//pthread_mutex_unlock(&mymutex2);
	}
}

