#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64
#define DELIM " \t\r\n"
// \t- tab, \n- new line, \r-carrige to the left position, without a new line

// 0 is not finished, 1 is finished
int is_finished(char **arg) {
    pid_t pid, wpid;
    int fin; 
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "is_finished: forking error \n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
//execvp gives a process an array of pointers to the strings, which finishes with null 
//arg[1]-arg[last]= parameters
//arg[0]- points to the name of the file to be  executed 
//last arg = NULL, otherwise - execption
        if (execvp( arg[0], arg) == -1){ 
             fprintf(stderr, "is_finished: forking error \n");
             exit(EXIT_FAILURE);
        }
    } else
        {
            do{
// waitpid - waits for the process to finish
// WUNTRACED returns the control even if there are child processes without execution/finish status
                wpid = waitpid(pid, &fin, WUNTRACED);
            }
// WIFEXITED!=0 is chils process has finished successfully
// WIFSIGNALED = 1 if child process has finished because of the untreated signal 
            while (!WIFEXITED(fin) && !WIFSIGNALED(fin));
        }
    return 1;
}

char **read_line() {
    char *line=NULL;
    char **parsed;
    int buf = BUFFER_SIZE;
    size_t len = 0;
    int pos = 0;

    parsed = calloc(buf, sizeof(char *));

    if (!parsed) {
        fprintf(stderr, "read_line: error with memory allocation\n");
        exit(EXIT_FAILURE);
    }

    if (getline(&line, &len, stdin) == -1) {
        fprintf(stderr, "read_line: reading error\n");
        exit(EXIT_FAILURE);
    };

    char *word;
    word = strtok(line, DELIM);
    while (word != NULL) {
        parsed[pos] = word;
        pos++;
// increasing the buffer and coping prev values to the increased version
        if (pos > buf) {
            buf = buf + BUFFER_SIZE;
            parsed = realloc(parsed, buf * sizeof(char *));
            if (!parsed) {
                fprintf(stderr, "read_line: error with memory allocation\n");
                exit(EXIT_FAILURE);
            }
        }
        word = strtok(NULL, DELIM);
    }
//mark the end
    parsed[pos] = NULL;
    return parsed;
}

void command_cycles() {
    char **command;
    int finished = 1;

    while (finished) {
        printf("waiting for a command");
        command = read_line();
        finished = is_finished(command);
    }
    //free memory
    free(command);
}

 int main() {

    //start command cycles
    command_cycles();
    return EXIT_SUCCESS;
}