#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main() {
    __pid_t pid = fork();

    if (pid == 0) {
        while (1) {
            printf("I'm alive!\n");
            sleep(1);
        }
        exit(0);
    } else {
        sleep(10);
        kill(pid, SIGTERM);
    }

    return 0;
}