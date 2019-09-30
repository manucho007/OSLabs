#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int pipefd[2];

int main() {
    int result = pipe(pipefd);

    if (result != 0) {
        printf("An error occured.\n");
        exit(-1);
    }

    if (fork() == 0) {
        char buffer2[BUFFER_SIZE];
        read(pipefd[0], buffer2, BUFFER_SIZE);
        printf("%s", buffer2);
        exit(0); 
    } else {
        const char buffer1[BUFFER_SIZE] = "Hello, world!\n";
        write(pipefd[1], buffer1, BUFFER_SIZE);
    }

    return 0;
}