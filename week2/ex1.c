#include <stdio.h>
#include <limits.h>
#include <float.h>
int main()
{
    //    Declare integer, float and double variable
    //    Assign maximum value to each variable
    int a = INT_MAX;
    float b = FLT_MAX;
    double c = DBL_MAX;
    //    Print value of variables
    printf("The values of the variable are the following:\n"
           "for the int: %d\n"
           "for the float: %f\n"
           "for the double: %f \n",
           a, b, c);
    //    Print size of variable
    printf("The size of the int in bytes is: %lu\n"
           "the size of the float in bytes is: %lu\n"
           "the size of the double in bytes is: %lu\n",
           sizeof(a), sizeof(b), sizeof(c));
    return 0;
}
