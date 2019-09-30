#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *work(void *arg) {
    int temp;

    temp = (int) arg;
    printf("Thread number %d.\n", temp);
    pthread_exit(NULL);

}

int main(){
    int threads = 5;


    for (short i = 0; i < threads; ++i) {
        pthread_t thread;

        printf("Creating thread %d\n", i);
        pthread_create(&thread, NULL, work, (void *) i);
        int message = pthread_join(thread, NULL);
        printf("Thread %d completed with code %d\n", i, message);
    }

    exit(0);
}