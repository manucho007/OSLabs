#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int pipefd[2];

    pipe(pipefd);

    __pid_t pid1st = fork();

    if (pid1st == 0) { // first child
        __pid_t pid2nd;
        read(pipefd[0], &pid2nd, sizeof(__pid_t));
        printf("1st child received PID of 2nd child (%d).\n", pid2nd);

        int status;
        waitpid(pid2nd, &status, 0);
        printf("1st child went to sleep...\n");
        sleep(5);
        kill(pid2nd, SIGSTOP);
        printf("1st child woke up and killed 2nd!!!\n");
        exit(0);
    } else {
        printf("1st child with PID=%d was created.\n", pid1st);
        __pid_t pid2nd = fork();

        if (pid2nd == 0) { // 2nd child
            while (1) {
                printf("2nd child is still alive...\n");
                sleep(1);
            }
        } else { // parent
            printf("2nd child with PID=%d was created.\n", pid2nd);

            printf("Parent started sending PID of 2nd child (%d).\n", pid2nd);
            write(pipefd[1], &pid2nd, sizeof(__pid_t));
            

            int status;
            waitpid(pid1st, &status, 0);
            printf("Parent with PID=%d finished waiting for all those actions.\n", getpid());
        }
    }

    return 0;
}