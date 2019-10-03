#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;
    printf("Enter the value of N: ");
    scanf("%d",&n);
    int *p1 = malloc(n* sizeof(int));
    if(p1){
        for(int i=0; i<=n;i++){
            p1[n]=n;
        }
        for(int i=0;i<=n;i++){
            printf("p1[%d] == %d\n", i, i);
        }
    } 
    free(p1);
}

