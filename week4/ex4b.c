#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define EXIT_CMD "exit"
#define MYBG_CMD "mybg"

char buffer[BUFFER_SIZE];

int processExit() {
    // check if command equals "exit"
    if (strcmp(buffer, EXIT_CMD) == 0) {
        exit(0);
    }

    // exit with failure
    return 0;
}

int processMyBg(char ** argv, char ** envp) {
    // check if stats with "mybg"
    if (strstr(buffer, MYBG_CMD) != buffer) return 0;

    // lenngth of "mybg"
    int myBgCmdLen = strlen(MYBG_CMD);
    // extract file name (assuming a single space character)
    char * fileName = buffer + myBgCmdLen + 1;

    // fork to create a background process.
    if (fork() == 0) {
        printf("Starting background process...\n");
        execve(fileName, argv, envp);
        exit(0);
    }

    // exit with success
    return 1;
}

int main(int argc, char ** argv, char ** envp) {

    while (1) {
        printf("$: ");
        // read command
        scanf("%s", buffer);
        
        if (processExit()) {
            // check for exit   
        }
        else if (processMyBg(argv, envp)) {
            // mybg [file_name] runs program in background
            // check if starts with "mybg"
        }
        else {
            system(buffer);
        }
    }

    return 0;
}