#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 10
#define BUFFER_SIZE 5

int num_of_items = 0, consuming = 0, producing = 0;

void wait(){
	usleep(5000);
}

void produce(){
	num_of_items++;
}

void consume(){
	num_of_items--;
}

void * producer(void *id_ptr){
	while(1){
		wait();
		
		// stop producing and (sleep)
		if(num_of_items == BUFFER_SIZE) producing = 0;
		while(!producing){}
		
		wait();

		// continue producing
		produce();
		
		// wake up consumer
		if(num_of_items == 1) consuming = 1;
	}
	return NULL;
}

void *consumer(void *id_ptr){
	while(1){
		
		// stop consuming and sleep
		if(num_of_items == 0) consuming = 0;
		while(!consuming){}

		wait();

		// continue consuming
		consume();

		// wake up producer
		if(num_of_items == BUFFER_SIZE - 1) producing = 1;	
		wait();
	}
	return NULL;
}

int main(){
	int id[MAX_THREADS];
	pthread_t t_id[MAX_THREADS];

	for(int i=0;i<MAX_THREADS;i++)
		id[MAX_THREADS] = i;
	
	// start producing
	producing = 1;
	
	// create the threads
	pthread_create(&t_id[0], NULL, producer, (void *) &id[0]);
	pthread_create(&t_id[1], NULL, consumer, (void *) &id[1]);
	
	// track status of the buffer
	while(consuming || producing){
		sleep(1);
		printf("the current number of items is: %d\n", num_of_items);
	}
	
	// stop execution of the thread due to a deadlock
	printf("fatal race condition error (Deadlock)\n");
	return 0;
}