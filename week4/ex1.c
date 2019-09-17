#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
    pid_t pid;
    pid = fork();
    int n = 10;
    for(int i=0;i<=n;i++)
    {
        if (pid > 0) { /* parent */
        printf("Hello from parent [%d - %d]\n", pid, i);
        } else if (pid == 0) { /* child */
        printf("Hello from child [%d - %d]\n", pid, i);
    } else { /* error */
        return EXIT_FAILURE;
    }
    }
    return EXIT_SUCCESS;
}

// for i in 1 2 3 4 5 6 7 8 9 10
// do
// ./ex4
// done


    // If fork() returns a negative value, the creation of a child process was unsuccessful.
    // fork() returns a zero to the newly created child process.
    // fork() returns a positive value, the process ID of the child process,
    // to the parent. The returned process ID is of type pid_t defined in sys/types.h.
    // Normally, the process ID is an integer. Moreover, a process can use function getpid() to retrieve the process ID assigned to this process. 