#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sighanlder(int code) {
    printf("Attempted to interrupt.\n");
}

int main() {
    printf("Started! My pid is %d.\n", getpid());
    signal(SIGINT, sighanlder);
    while (1) {}

    return 0;
}