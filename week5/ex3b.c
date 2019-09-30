# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>


int size = 5;
int buffer_index = 0;
char *buffer;

void *producer() {
    while (1) {
        if (buffer_index == size) continue;
        buffer[buffer_index++] = '1';
        printf("produce: %d \n", buffer_index);
    }

}

void *consumer() {
    while (1) {
        if (buffer_index == 0) continue;

        buffer_index--;

        printf("consumer: %d \n", buffer_index);
    }
}

int main() {
    int size = 5;
    pthread_t producer_thread;
    pthread_t consumer_thread;

    buffer = (char *) malloc(sizeof(char) * size);

    pthread_create(&producer_thread, NULL, producer(size), NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);


    return 0;
} 