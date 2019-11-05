//
// Created by valentun on 30.10.19.
//

#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int in_fd = open("ex1.txt", O_RDWR);

    char *in_buffer, *out_buffer;

    struct stat file_stat;

    fstat(in_fd, &file_stat);

    size_t file_size = (size_t)file_stat.st_size;

    in_buffer = mmap(0, file_size, PROT_READ, MAP_SHARED, in_fd, 0);

    int out_fd = open("ex1.memcpy.txt", O_RDWR);

    ftruncate(out_fd, file_size);

    out_buffer = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, out_fd, 0);

    memcpy(out_buffer, in_buffer, file_size);
}