#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int flag = 1;
struct sigaction act;

void handler(int signum, siginfo_t *info, void *ptr)
{
    printf("Received signal %d\n", signum);
    printf("Signal sender: %lu\n", (unsigned long)info->si_pid);
	
    if(signum == SIGTERM)
    {
    	printf("Terminating from SIGTERM\n");
		flag = 0; 
    }
    else if (signum == SIGSTOP)
    {
    	printf("Terminating from SIGSTOP\n");
		flag = 0; 
    }
    else if (signum == SIGUSR1)
    {
    	printf("Terminating from SIGUSR1\n");
		flag = 0; 
    }
}

int main(int argc, char const *argv[])
{
	memset(&act, 0, sizeof(act));

    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGSTOP, &act, NULL);

	while(flag)
	{
		printf("Doing something\n");
		sleep(2);
	}
	return 0;
}