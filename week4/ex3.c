#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *cmd = (char*) malloc(sizeof(char)*100);
	char buf[1024];	
	while(1){
		fgets(buf, 1023, stdin);
	//	scanf("%s", cmd);
		if(strcmp("exit", buf)==0){
			break;
		}else{
			system(buf);
		}
	}
	return 0;
}