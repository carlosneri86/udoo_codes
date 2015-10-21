#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>


void* ThreadHelloWorld(void * argv);


int main (int argc, char **argv)
{
	pthread_t thread;
	uint32_t max_threads = 0;
	uint32_t thread_offset= 0;
    
	printf("Creating %s thread\n",argv[1]);	
    
	if(argc < 2)
	{
		printf("Need more threads!");
		return (1);
	}

	max_threads = atoi(argv[1]);

	while(thread_offset < max_threads)
	{
		(void)pthread_create(&thread, NULL, &ThreadHelloWorld,(void*)&thread_offset );
		(void)pthread_join(thread,NULL);
		thread_offset++;
	

	}

	printf("Exiting now!!\n");
    return(1);
}

void * ThreadHelloWorld(void * argv)
{
	uint32_t * ThreadID = (uint32_t*)argv; 

	printf("Hellow World from Thread: %d\n",*ThreadID);
	
	pthread_exit(NULL);
}
