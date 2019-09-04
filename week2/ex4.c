#include <stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
};
int main()
{
    int a;
    int b;
    printf("Enter the first digit");
    scanf_s("%d", &a);
    printf("Enter the second digit");
    scanf_s("%d", &b);
    swap(&a, &b);
    printf("The swapped values are: \n%d, %d", a, b);
}
