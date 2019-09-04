#include <stdio.h>
#include <stdlib.h>
void print_rsu_triangle(int n);
int main(void)
{
    int num;
    //    char term;
    if (scanf("%d", &num) != 1)
    {
        printf("Please write a valid number\n");
        return EXIT_FAILURE;
    }
    else
        print_rsu_triangle(num);
}
void print_rsu_triangle(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            putchar(' ');
        }
        for (int k = n - i; k < n + i - 1; k++)
        {
            putchar('*');
        }
        putchar('\n');
    }
}
