#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <memory.h>
#include <unistd.h>

int main(void)
{
    FILE *source_file = fopen("ex4.txt", "r");
    struct stat st;
    stat("ex4.txt", &st);
    off_t source_size = st.st_size;
    fclose(source_file);

    FILE *destination_file = fopen("ex4.memcpy.txt", "w");
    ftruncate(fileno(destination_file), source_size);
    fclose(destination_file);

    int s_file = open("ex4.txt", O_RDWR);
    int d_file = open("ex4.memcpy.txt", O_RDWR);

    char *s_map;
    s_map = mmap(NULL, source_size, PROT_READ | PROT_WRITE, MAP_SHARED, s_file, 0);

    char *d_map;
    d_map = mmap(NULL, source_size, PROT_READ | PROT_WRITE, MAP_SHARED, d_file, 0);

    memcpy(d_map, s_map, source_size);

    return 0;
}