#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct page_frame
{
    int page, age;
};

int main()
{
    int frames_num;
    int hits_num = 0;
    int references = 0;

    printf("Page frames: ");
    scanf("%d", &frames_num);

    struct page_frame *frame = calloc(frames_num, sizeof(struct page_frame));
    FILE *input = fopen("input.txt", "r");
    char c = fgetc(input);
    int page_number = 0;

    while (c != EOF)
    {
        if (c == ' ')
        {
            int hit = 0;
            int to_replace = 0;
            int max_age = 0;

            for (int i = 0; i < frames_num; i++)
            {
                if (frame[i].page == 0)
                {
                    max_age = 16;
                    to_replace = i;
                }
                else
                {
                    if (frame[i].page == page_number)
                    {
                        hit = 1;
                        hits_num++;
                        frame[i].age = 0;
                    }
                    else
                    {
                        frame[i].age++;
                        if (frame[i].age > max_age)
                        {
                            max_age = frame[i].age;
                            to_replace = i;
                        }
                    }
                }
            }
            if (hit == 0)
            {
                frame[to_replace].page = page_number;
                frame[to_replace].age = 0;
            }
            references++;
            hit = 0;
            max_age = 0;
            page_number = 0;
        }
        else
        {
            page_number = page_number * 10;
            page_number = page_number + ((int)c - 48);
        }
        c = getc(input);
    }

    printf("Hit/Miss Ratio = %f\n", ((float)hits_num / (float)references));

    fclose(input);
    return 0;
}