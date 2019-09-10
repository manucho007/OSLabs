#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
    pid_t pid;
    pid = fork();
    int n = 811;
    if (pid > 0) { /* parent */
        printf("Hello from parent [%d - %d]\n", pid, n);
    } else if (pid == 0) { /* child */
        printf("Hello from child [%d - %d]\n", pid, n);
    } else { /* error */
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// for i in 1 2 3 4 5 6 7 8 9 10
// do
// ./ex4
// done