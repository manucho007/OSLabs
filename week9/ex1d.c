#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <stdio.h>

int main()
{
    int n, miss, hit; // n - amount of pages frames in physical memory
    printf("%s", "Number of page frames: ");
    scanf("%d", &n);
    miss = 0;
    hit = 0;

    int *mem = (int *)(malloc(sizeof(int) * n));  // an array for page frames
    int *ages = (int *)(malloc(sizeof(int) * n)); // array of ages of page frames
    memset(ages, 0, n);                           // initially all of them are 0

    FILE *file;
    file = fopen("input.txt", "r");

    int new_page; //variable for reading new page

    while (fscanf(file, "%d", &new_page) != EOF)
    {
        int miss_page = 1, index = 0; // miss_page - flag to find out whether we found needed page or not, index - index of found page

        /* trying to find needed page*/
        for (int i = 0; i < n; i++)
        {
            if (mem[i] == new_page)
            {
                miss_page = 0; // set a flag to zero as we found needed page
                index = i;
            }
        }
        /* if there is no needed page in physical memory */
        if (miss_page == 1)
        {
            miss += 1;
            int min = ages[0];
            int min_index = 0;

            /* finding the oldest page in memory*/
            for (int i = 0; i < n; i++)
            {
                if (ages[i] < min)
                {
                    min = ages[i];
                    min_index = i;
                }
            }
            mem[min_index] = new_page;
            ages[min_index] = ages[min_index] | (1 << 7);
        }
        /* if there is needed page in memory*/
        else
        {
            hit += 1;
            ages[index] = ages[index] | (1 << 7);
        }
        /* updating all ages*/
        for (int i = 0; i < n; i++)
        {
            if (mem[i] != new_page)
                ages[i] = ages[i] >> 1;
        }
    }
    fclose(file);
    //printf("%d %d ", hit, miss);
    double ratio = (double)hit / (double)miss;
    printf("%s %lf \n", "Hit/miss ratio: ", ratio);
    return 0;
}