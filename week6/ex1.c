#include <stdio.h>
int main (void) {
char* string = "Hello";
char buf[1024];
int fds[2];
pipe(fds);
printf("buf content before: %s\n", buf);
write(fds[1], string, 6);
read(fds[0], buf, 6);
close(fds[0]);
close(fds[1]);
printf("buf content after: %s\n", buf);
}