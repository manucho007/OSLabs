#include <stdio.h>
#include <stdlib.h>
#define DEFAULT 10
#define NUMBER_BITS 16
/*
	10 hit = 9.000000 miss = 991.000000 ratio = 0.009082
	50 hit = 51.000000 miss = 949.000000 ratio = 0.053741
	100 hit = 94.000000 miss = 906.000000 ratio = 0.103753
*/
typedef struct page
{
	int id;
	unsigned counter : NUMBER_BITS;
} page;

FILE *file;

int main(int argc, char const *argv[])
{
	float hit = 0, miss = 0;
	int num_of_pages = DEFAULT;
	printf("Print the number of pages\n");
	scanf("%d", &num_of_pages);

	file = fopen("input.txt", "r");

	page *pages = calloc(num_of_pages, sizeof(page));

	int cur_page;

	for (int i = 0; i < num_of_pages; i++)
	{
		pages[i].counter = 0;
		pages[i].id = -1;
	}

	while (fscanf(file, "%d", &cur_page) != EOF)
	{
		for (int i = 0; i < num_of_pages; i++)
		{
			printf("i = %d id = %d", i, pages[i].id);
			char buffer[64];
			snprintf(buffer, sizeof(buffer), "%d", pages[i].counter);
			printf(" %s\n", buffer);
		}
		int candidate = -1;
		int least = pages[0].counter;
		for (int i = 0; i < num_of_pages; i++)
		{
			pages[i].counter >>= 1;
			if (pages[i].id == -1 && candidate == -1)
			{
				candidate = i;
			}
			if (pages[i].id == cur_page)
			{
				candidate = i;
			}
			if (least > pages[i].counter && candidate == -1)
			{
				least = pages[i].counter;
			}
		}

		if (pages[candidate].id == cur_page)
		{
			pages[candidate].counter |= 1 << (NUMBER_BITS - 1);
			hit++;
		}
		else
		{
			miss++;
			pages[candidate].counter = 0;
			pages[candidate].id = cur_page;
			pages[candidate].counter |= 1 << (NUMBER_BITS - 1);
		}
		candidate = -1;
		printf("\n");
	}

	printf("hit = %f miss = %f ratio = %f\n", hit, miss, hit / miss);

	return 0;
}