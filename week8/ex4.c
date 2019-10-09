#include <stdio.h> 
#include <time.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

extern int errno;

int main() 
{ 
    struct rusage * usage = malloc(sizeof(struct rusage));
    int mb = 1024*1024;
    for (int i = 0; i < 10; i++) { 
        memset(calloc(10*mb, 1), 1, 10*mb);
        if (getrusage(RUSAGE_SELF, usage)) {
            printf("Error %d\n", errno);
        };
        printf("ru_maxrss = %ld\n",(*usage).ru_maxrss);
        sleep(1); 
    } 
   
    return 0; 
}