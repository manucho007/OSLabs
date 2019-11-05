#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    struct stat *buff = malloc(sizeof(struct stat));
    stat("ex1.txt", buff);
    // FILE *f;
    int file = open("ex1.txt", O_RDWR);
    char *new_addr;
    new_addr = mmap(NULL, buff->st_size, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
    char *str = "This is a nice day";
    int i;
    for (i = 0; i < 21; i++)
    {
        new_addr[i] = str[i];
    }
    return 0;
}