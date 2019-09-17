#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *cmd = (char*) malloc(sizeof(char)*100);

    while(1){

        scanf("%s", cmd);
        if(strcmp("quit", cmd)==0){
            break;
        }else{
            char delim[] = " ";
            char *ptr = strtok(cmd, delim);
            char **cmd_arg;
            cmd_arg = (char**)malloc(sizeof(cmd)*strlen(cmd));
            int i=0;
            while(ptr != NULL){
                //cmd_arg[i] = ptr;
                printf("%s %d", ptr, i);

                system(*cmd_arg);
            }
        }
        return 0;
    }}