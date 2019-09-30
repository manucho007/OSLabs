#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX=50;
void* producer(void *ptr) {   
    int i;
        for (i = 1; i <= MAX; i++) {
         /* produce */
        }   
            pthread_exit(0);
         }
void* consumer(void *ptr) {

 }
int main(int argc, char **argv) {   
    pthread_t pro, con;   
    pthread_create(&con, NULL, consumer, NULL);   
    pthread_create(&pro, NULL, producer, NULL);   
    pthread_join(con, NULL);   
    pthread_join(pro, NULL); 
    }