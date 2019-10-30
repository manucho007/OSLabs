#include <fcntl.h>
#include <unistd.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *file;
    file = freopen("ex2.txt", "w", stdout);
    printf("H");
    sleep(1);
    printf("e");
    sleep(1);
    printf("l");
    sleep(1);
    printf("l");
    sleep(1);
    printf("o");
    sleep(1);

    fclose(file);

    return 0;
}