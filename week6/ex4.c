#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int catched_signal = 0;

void sighanlder(int code) {
    switch (code) {
        case SIGKILL: printf("Attempted to kill!\n"); break;
        case SIGSTOP: printf("Attempted to stop!\n"); break;
        case SIGUSR1: printf("User defined signal!\n"); break;

        default: printf("Some other signal!\n"); break;
    }

    catched_signal = 1;
}

int main() {
    printf("Started! My pid is %d.\n", getpid());

    signal(SIGKILL, sighanlder);
    signal(SIGSTOP, sighanlder);
    signal(SIGUSR1, sighanlder);

    while (!catched_signal) {}

    printf("Finished!\n");

    // Program intercepts SIGUSR1 signal. When kill -SIGUSR1 <pid> is called, SIGUSR1 signal is sent. 
    // Program responds and prints 'User defined signal!'

    return 0;
}