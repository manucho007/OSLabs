#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int mb = 1024*1024;
    for (int i = 0; i < 10; i++) {
        printf("cycle %d \n",i+1);
        memset(calloc(10*mb, 1), 0, 10*mb);
        sleep(1);
    }
    return 0;
}