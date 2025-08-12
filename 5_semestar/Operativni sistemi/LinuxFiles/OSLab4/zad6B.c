#include "implicit.h"

int main(int argc, char* argv[])
{
	int i;
	char c;
	int pd;
	FILE *f;

	if(argc < 2)
	{
		printf("Nedovoljno argumenata!\n");
		return -1;
	}

	f = fopen("chars.txt", "w");

	if(!f)
	{
		printf("Greska pri otvaranju fajla!\n");
		return -1;
	}

	pd = atoi(argv[1]);

	for(i = 0; i < 25; i++)
	{
		read(pd, &c, 1);
		fprintf(f, "%c\n", c);
	}

	close(pd);

	return 0;

}
