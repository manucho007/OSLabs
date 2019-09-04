#include <stdio.h>
#include <string.h>
#define MAX_LEN 50
int main(void)
{
    char str[MAX_LEN];
    int i;
    puts("Enter a string");
    fgets(str, MAX_LEN, stdin);
    printf("Your string reversed is: \n");
    for (i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == '\n')
            continue;
        else
            putchar(str[i]);
    }
    return 0;
}