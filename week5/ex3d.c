#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define JAR_CAPACITY 10

typedef struct stack_t
{
	int jar[JAR_CAPACITY];	
	int cur_size;
} Stack;


void *Producer(void *vararg)
{
	Stack *stack = (Stack*)vararg;

	while(1)
	{	
		while (stack->cur_size == JAR_CAPACITY){}

		int c = rand() % 10;
    	printf("Yay, new cookie: %d\n", c);

    	stack->jar[stack->cur_size++] = c;
    }
}

void *Consumer(void *vararg)
{
	Stack *stack = (Stack*)vararg;

	while(1)
	{
    	while (stack->cur_size == 0){}

    	printf("I ate: %d Om Nom Nom\n", stack->jar[--stack->cur_size]);
    }
}

int main(int argc, char const *argv[])
{
	Stack s = {.cur_size = 0};

	pthread_t p, c;
	pthread_create(&p, NULL, Producer, (void*)&s);
	pthread_create(&c, NULL, Consumer, (void*)&s);	

	pthread_join(p, NULL); 
    pthread_join(c, NULL);
	return 0;
}