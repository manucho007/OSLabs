
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("ex1.txt", O_RDWR);

    char *buffer;

    struct stat file_stat;

    fstat(fd, &file_stat);

    size_t file_size = (size_t)file_stat.st_size;

    buffer = mmap(0, file_size, PROT_WRITE, MAP_SHARED, fd, 0);
    char *to_write = "This is a nice day";

    size_t new_len = strlen(to_write);

    memcpy(buffer, to_write, new_len);
    memset(buffer + new_len, 0, file_size - new_len);
}